/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:56:58 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 14:40:18 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	print_cycle(t_vm *vm)
{
	SDL_Rect	coord;
	SDL_Rect	printed;

	printed.x = 0;
	printed.y = 0;
	printed.h = 7;
	printed.w = ((vm->cycle_to_die - vm->cycle_left_to_die % vm->cycle_to_die)
	* vm->visu.memory_coord.w) / vm->cycle_to_die;
	coord.x = vm->visu.memory_coord.x;
	coord.y = vm->visu.memory_coord.h + vm->visu.memory_coord.y;
	SDL_BlitSurface(vm->visu.cycle, &printed, vm->visu.window_surface, &coord);
}

void	print_all(t_vm *vm)
{
	print_memory(vm);
	print_cycle(vm);
	print_log(vm);
	SDL_UpdateWindowSurface(vm->visu.window);
}

void	slow_visu(t_vm *vm, unsigned int slow_time)
{
	slow_time += SDL_GetTicks();
	while (SDL_GetTicks() < slow_time)
	{
		get_event(vm);
		print_log(vm);
		SDL_UpdateWindowSurface(vm->visu.window);
	}
}

void	print_mem(t_vm *vm)
{
	if (vm->visu.speed > 0 && vm->cycle % vm->visu.speed)
		return ;
	print_all(vm);
	if (vm->visu.speed < 0)
		slow_visu(vm, vm->visu.frame_speed * vm->visu.speed * -1);
	get_event(vm);
}
