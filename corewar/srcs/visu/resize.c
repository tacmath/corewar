/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resize.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:58:01 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 15:13:56 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	free_text(t_vm *vm)
{
	int n;

	n = -1;
	while (++n < 16)
		SDL_FreeSurface(vm->visu.hex[n]);
	n = -1;
	while (++n < 4)
		SDL_FreeSurface(vm->visu.info_text[n]);
	n = -1;
	while (++n < 24)
		if (n != 7)
			SDL_FreeSurface(vm->visu.process_text[n / 8][n % 8]);
	n = -1;
	while (++n < 6)
		SDL_FreeSurface(vm->visu.command_text[n]);
	TTF_CloseFont(vm->visu.info_font);
}

void	free_all_old_images(t_vm *vm)
{
	int n;

	free_text(vm);
	n = -1;
	while (++n < 4)
	{
		SDL_FreeSurface(vm->visu.champ_name[n]);
		SDL_FreeSurface(vm->visu.champ[n]);
		SDL_FreeSurface(vm->visu.champ_jauge[n]);
		SDL_FreeSurface(vm->visu.champ_jauge_halo[n]);
	}
	SDL_FreeSurface(vm->visu.process);
	SDL_FreeSurface(vm->visu.arena);
	SDL_FreeSurface(vm->visu.log);
	SDL_FreeSurface(vm->visu.little_info);
	SDL_FreeSurface(vm->visu.cycle);
	SDL_FreeSurface(vm->visu.highlight);
}

void	free_images_src(t_vm *vm)
{
	int n;

	n = -1;
	while (++n < 4)
	{
		SDL_FreeSurface(vm->visu.champ_src[n]);
		SDL_FreeSurface(vm->visu.champ_jauge_src[n]);
		SDL_FreeSurface(vm->visu.champ_jauge_halo_src[n]);
	}
	SDL_FreeSurface(vm->visu.process_src);
	SDL_FreeSurface(vm->visu.log_background);
	SDL_FreeSurface(vm->visu.arena_background);
}

void	resize_window(t_vm *vm, int x, int y)
{
	if (y < 300)
		y = 300;
	free_all_old_images(vm);
	init_coord(vm, x, y);
	SDL_SetWindowSize(vm->visu.window, vm->visu.win_len.w, vm->visu.win_len.h);
	if (!init_text(vm) || !(vm->visu.window_surface =
SDL_GetWindowSurface(vm->visu.window)) || !init_cycle(vm) || !init_info(vm))
		return ;
	if (!(vm->visu.arena = SDL_CreateRGBSurface(0, vm->visu.arena_coord.w,
					vm->visu.arena_coord.h, 32, 0, 0, 0, 0)) ||
		!(vm->visu.log = SDL_CreateRGBSurface(0, vm->visu.log_coord.w,
				vm->visu.log_coord.h, 32, 0, 0, 0, 0)))
		return ;
	SDL_BlitScaled(vm->visu.arena_background, 0, vm->visu.arena, 0);
	SDL_BlitScaled(vm->visu.log_background, 0, vm->visu.log, 0);
	if (!(init_champ_name(vm)))
		return ;
	resize_all_images(vm);
	init_info_text(vm);
	vm->visu.frame_speed = SDL_GetTicks();
	print_all(vm);
	vm->visu.frame_speed = SDL_GetTicks() - vm->visu.frame_speed;
}
