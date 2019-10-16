/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:56:15 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/29 13:57:45 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void		init_coord(t_vm *vm, int win_width, int win_height)
{
	win_width = 1.77 * win_height;
	vm->visu.win_len.w = win_width;
	vm->visu.win_len.h = win_height;
	vm->visu.memory_coord.x = vm->visu.win_len.w / 80;
	vm->visu.memory_coord.y = vm->visu.win_len.h / 55;
	vm->visu.win_len.h -= (vm->visu.win_len.h - vm->visu.memory_coord.y * 2 - 7)
	% ft_sqrt(MEM_SIZE);
	vm->visu.log_coord.h = vm->visu.win_len.h;
	vm->visu.log_coord.w = (vm->visu.win_len.h * FRAME_WIDTH) / FRAME_LEN;
	vm->visu.memory_coord.w = vm->visu.win_len.w - vm->visu.log_coord.w -
	vm->visu.memory_coord.x * 2;
	vm->visu.memory_coord.w -= vm->visu.memory_coord.w % ft_sqrt(MEM_SIZE);
	vm->visu.memory_coord.h = vm->visu.win_len.h - 7 - vm->visu.memory_coord.y
	* 2;
	vm->visu.arena_coord.w = vm->visu.memory_coord.w + vm->visu.memory_coord.x
	* 2;
	vm->visu.arena_coord.h = vm->visu.win_len.h;
	vm->visu.win_len.w = vm->visu.arena_coord.w + vm->visu.log_coord.w;
	vm->visu.log_coord.x = vm->visu.arena_coord.w;
	vm->visu.log_coord.y = 0;
	vm->visu.memory_coord.x += 3;
	vm->visu.mem_len.h = (vm->visu.memory_coord.h / ft_sqrt(MEM_SIZE));
	vm->visu.mem_len.w = ((vm->visu.memory_coord.w) / ft_sqrt(MEM_SIZE));
}

int			init_visu_if(t_vm *vm, int choice)
{
	if (choice == 0)
		return (
		!(vm->visu.window = SDL_CreateWindow("CoreWar", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, vm->visu.win_len.w, vm->visu.win_len.h,
		SDL_WINDOW_RESIZABLE)));
	else if (choice == 1)
		return (
		!(vm->visu.window_surface = SDL_GetWindowSurface(vm->visu.window)) ||
		!init_text(vm) || !init_info(vm) || !load_images(vm));
	else if (choice == 2)
		return (
		!(vm->visu.arena = SDL_CreateRGBSurface(0, vm->visu.arena_coord.w,
		vm->visu.arena_coord.h, 32, 0, 0, 0, 0)) ||
		!(vm->visu.log = SDL_CreateRGBSurface(0, vm->visu.log_coord.w,
		vm->visu.log_coord.h, 32, 0, 0, 0, 0)));
	else
		return (0);
}

static void	init_process_visu(t_vm *vm)
{
	int	n;

	n = -1;
	while (++n < MEM_SIZE)
		vm->arena.processes[n] = -1;
}

int			init_visu(t_vm *vm)
{
	srand(time(NULL));
	init_coord(vm, WINDOWS_HEIGHT, WINDOWS_HEIGHT);
	vm->visu.speed = 1;
	vm->visu.mode = 1;
	vm->options.visu_intro = 1;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) || TTF_Init())
		return (0);
	if (Mix_OpenAudio(11025, AUDIO_S8, MIX_DEFAULT_CHANNELS, 1024))
		return (0);
	if (init_visu_if(vm, 0))
		return (0);
	if (vm->options.visu_intro)
		launch_intro(vm);
	if (init_visu_if(vm, 1) || init_visu_if(vm, 2))
		return (0);
	SDL_BlitScaled(vm->visu.arena_background, 0, vm->visu.arena, 0);
	SDL_BlitScaled(vm->visu.log_background, 0, vm->visu.log, 0);
	if (!init_champ_name(vm) || !resize_all_images(vm) || !init_info_text(vm))
		return (0);
	play_music(vm);
	init_process_visu(vm);
	vm->visu.frame_speed = SDL_GetTicks();
	print_all(vm);
	vm->visu.frame_speed = SDL_GetTicks() - vm->visu.frame_speed;
	return (1);
}
