/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   pause.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:56:45 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 15:05:21 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	pause_visu2(t_vm *vm, SDL_Event event, int *pause)
{
	if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
					|| event.window.event == SDL_WINDOWEVENT_CLOSE)
	{
		print_process(vm, 0, RESET);
		print_instr(vm, 0, RESET);
		quit_visu(vm);
	}
	if (event.window.event == SDL_WINDOWEVENT_RESIZED)
		resize_window(vm, event.window.data1, event.window.data2);
	if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
	{
		print_process(vm, 0, RESET);
		print_instr(vm, 0, RESET);
		*pause = 0;
	}
	if (event.type == SDL_MOUSEMOTION)
		print_info(vm, event.motion.x, event.motion.y);
	if (event.button.type == SDL_MOUSEBUTTONDOWN)
	{
		vm->visu.info_pages++;
		if (vm->visu.info_pages > 3)
			vm->visu.info_pages = 1;
		print_info(vm, event.button.x, event.button.y);
	}
}

static int	pause_visu3(t_vm *vm, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym ==
				SDLK_KP_PLUS && vm->visu.speed < 64)
	{
		vm->visu.speed = vm->visu.speed < 1 ? vm->visu.speed / 2 :
		vm->visu.speed * 2;
		if (vm->visu.speed == -1)
			vm->visu.speed = 1;
		print_log(vm);
		SDL_UpdateWindowSurface(vm->visu.window);
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym ==
			SDLK_KP_MINUS && vm->visu.speed > -64)
	{
		if (vm->visu.speed < 1)
			vm->visu.speed *= 2;
		else
			vm->visu.speed = vm->visu.speed > 1 ? vm->visu.speed / 2 : -2;
		print_log(vm);
		SDL_UpdateWindowSurface(vm->visu.window);
	}
	else
		return (1);
	return (0);
}

static void	pause_visu4(t_vm *vm, SDL_Event event, SDL_Rect mouse, int mem)
{
	if (pause_visu3(vm, event) && event.type == SDL_KEYDOWN
				&& event.key.keysym.sym == SDLK_r)
	{
		vm->visu.speed = 1;
		print_log(vm);
		SDL_UpdateWindowSurface(vm->visu.window);
	}
	if (event.wheel.type == SDL_MOUSEWHEEL)
	{
		SDL_GetMouseState(&mouse.x, &mouse.y);
		mouse.y -= vm->visu.memory_coord.y;
		mouse.x -= vm->visu.memory_coord.x;
		mem = (mouse.y / vm->visu.mem_len.h) * ft_sqrt(MEM_SIZE) +
		(mouse.x / vm->visu.mem_len.w);
		if (mem > 0 && mem < MEM_SIZE && mouse.x >= 0 && mouse.x <
	vm->visu.memory_coord.w && mouse.y > 0 && vm->arena.processes[mem] <= 100)
		{
			if (event.wheel.y > 0)
				print_process(vm, mem, PREVIOUS_PROCESS);
			if (event.wheel.y < 0)
				print_process(vm, mem, NEXT_PROCESS);
		}
	}
}

void		pause_visu(t_vm *vm)
{
	SDL_Event	event;
	SDL_Rect	mouse;
	int			pause;
	int			mem;

	mem = 0;
	pause = 1;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	print_info(vm, mouse.x, mouse.y);
	while (pause)
	{
		SDL_Delay(1);
		while (SDL_PollEvent(&event))
		{
			pause_visu2(vm, event, &pause);
			pause_visu4(vm, event, mouse, mem);
		}
	}
}
