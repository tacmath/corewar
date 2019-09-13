/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   intro.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/10 15:29:55 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 16:38:03 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static SDL_Rect	get_intro_coord(t_vm *vm, SDL_Surface *intro_image)
{
	SDL_Rect coord;

	vm->visu.window_surface = SDL_GetWindowSurface(vm->visu.window);
	if ((vm->visu.win_len.h * intro_image->w) / intro_image->h <
			vm->visu.win_len.w)
	{
		coord.w = (vm->visu.win_len.h * intro_image->w) / intro_image->h;
		coord.h = vm->visu.win_len.h;
		coord.x = vm->visu.win_len.w / 2 - coord.w / 2;
		coord.y = 0;
	}
	else
	{
		coord.w = vm->visu.win_len.w;
		coord.h = (vm->visu.win_len.w * intro_image->h) / intro_image->w;
		coord.x = 0;
		coord.y = vm->visu.win_len.h / 2 - coord.h / 2;
	}
	return (coord);
}

static void		get_shade(SDL_Surface *ref_image,
		SDL_Surface *image_shaded, int shade)
{
	SDL_Color	*pixel;
	int			n;

	SDL_BlitSurface(ref_image, 0, image_shaded, 0);
	SDL_LockSurface(image_shaded);
	pixel = (SDL_Color*)image_shaded->pixels;
	n = -1;
	while (++n < ref_image->w * ref_image->h)
	{
		pixel[n].r = (pixel[n].r * shade) / 50;
		pixel[n].g = (pixel[n].g * shade) / 50;
		pixel[n].b = (pixel[n].b * shade) / 50;
		pixel[n].a = (pixel[n].a * shade) / 50;
	}
	SDL_UnlockSurface(image_shaded);
}

static int		launch_intro2(t_vm *vm, SDL_Surface **intro_image,
		SDL_Surface **shaded_image, SDL_Rect *coord)
{
	char *tmp;

	tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, IMAGE_PATH,
			"IntroCoreWar.png");
	*intro_image = IMG_Load(tmp);
	SDL_SetSurfaceBlendMode(*intro_image, SDL_BLENDMODE_NONE);
	if (!(*shaded_image = SDL_CreateRGBSurface(0,
			(*intro_image)->w, (*intro_image)->h, 32, 0, 0, 0, 0)))
		return (0);
	get_shade(*intro_image, *shaded_image, 0);
	SDL_BlitScaled(*shaded_image, 0, vm->visu.window_surface, coord);
	SDL_UpdateWindowSurface(vm->visu.window);
	*coord = get_intro_coord(vm, *intro_image);
	free(tmp);
	return (1);
}

static int		intro_event(t_vm *vm, SDL_Surface *intro_image,
	SDL_Surface *shaded_image, SDL_Rect *coord)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				|| event.window.event == SDL_WINDOWEVENT_CLOSE)
		{
			SDL_FreeSurface(intro_image);
			SDL_FreeSurface(shaded_image);
			quit_visu(vm);
		}
		else if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		{
			init_coord(vm, event.window.data1, event.window.data2);
			SDL_SetWindowSize(vm->visu.window,
				vm->visu.win_len.w, vm->visu.win_len.h);
			*coord = get_intro_coord(vm, intro_image);
		}
		else if (event.type == SDL_KEYDOWN &&
			event.key.keysym.sym != SDLK_ESCAPE)
			return (1);
	}
	return (0);
}

void			launch_intro(t_vm *vm)
{
	SDL_Rect	coord;
	SDL_Surface	*intro_image;
	SDL_Surface	*shaded_image;
	int			shade;

	shade = 0;
	if (!launch_intro2(vm, &intro_image, &shaded_image, &coord))
		return ;
	while (1)
	{
		if (intro_event(vm, intro_image,
			shaded_image, &coord) || SDL_GetTicks() > 4000)
		{
			SDL_FreeSurface(intro_image);
			SDL_FreeSurface(shaded_image);
			return ;
		}
		else if (shade < 50)
		{
			get_shade(intro_image, shaded_image, ++shade);
			SDL_BlitScaled(shaded_image, 0, vm->visu.window_surface, &coord);
			SDL_UpdateWindowSurface(vm->visu.window);
		}
		SDL_Delay(10);
	}
}
