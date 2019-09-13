/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   end.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:55:32 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 18:14:39 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static SDL_Rect	get_end_coord(t_vm *vm, SDL_Surface *end_image)
{
	SDL_Rect coord;

	vm->visu.window_surface = SDL_GetWindowSurface(vm->visu.window);
	SDL_FillRect(vm->visu.window_surface, 0, 0);
	vm->visu.win_len.w = vm->visu.window_surface->w;
	vm->visu.win_len.h = vm->visu.window_surface->h;
	if ((vm->visu.win_len.h * end_image->w) / end_image->h < vm->visu.win_len.w)
	{
		coord.w = (vm->visu.win_len.h * end_image->w) / end_image->h;
		coord.h = vm->visu.win_len.h;
		coord.x = vm->visu.win_len.w / 2 - coord.w / 2;
		coord.y = 0;
	}
	else
	{
		coord.w = vm->visu.win_len.w;
		coord.h = (vm->visu.win_len.w * end_image->h) / end_image->w;
		coord.x = 0;
		coord.y = vm->visu.win_len.h / 2 - coord.h / 2;
	}
	return (coord);
}

static int		print_winer(t_vm *vm, SDL_Surface *end_image, char *font_path)
{
	TTF_Font			*font;
	SDL_Rect			coord;
	SDL_Surface			*text;
	static SDL_Color	color = {0, 184, 241, 0};

	coord = get_end_coord(vm, end_image);
	font = TTF_OpenFont(font_path, coord.h / 10);
	if (vm->last_live == -1)
		text = TTF_RenderText_Blended(font, "DRAW", color);
	else
	{
		vm->champs_decoded[vm->last_live].header.prog_name[15] = 0;
		text = TTF_RenderText_Blended(font,
		vm->champs_decoded[vm->last_live].header.prog_name, color);
	}
	TTF_CloseFont(font);
	if (!text)
		return (1);
	SDL_BlitScaled(end_image, 0, vm->visu.window_surface, &coord);
	coord.x += coord.w / 2 - text->w / 2;
	coord.y += coord.h * 0.732 - text->h / 2;
	SDL_BlitSurface(text, 0, vm->visu.window_surface, &coord);
	SDL_FreeSurface(text);
	SDL_UpdateWindowSurface(vm->visu.window);
	return (1);
}

void			print_end(t_vm *vm, char *end, char *font)
{
	char		*tmp;
	SDL_Event	event;
	SDL_Surface	*end_image;

	tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, IMAGE_PATH, end);
	end_image = IMG_Load(tmp);
	free(tmp);
	if (!(tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, FONT_PATH, font)))
		return ;
	print_winer(vm, end_image, tmp);
	while (1)
	{
		SDL_Delay(30);
		while (SDL_PollEvent(&event))
		{
			if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
					|| event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				SDL_FreeSurface(end_image);
				quit_visu(vm);
			}
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
				print_winer(vm, end_image, tmp);
		}
	}
}
