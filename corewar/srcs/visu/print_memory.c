/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_memory.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:38:23 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 12:39:01 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	print_number(t_vm *vm, int n, int m)
{
	SDL_Rect	coord;
	int			start_x;
	int			start_y;

	if (vm->arena.champs[n])
	{
		start_x = vm->visu.memory_coord.x + (n % m) *
			(vm->visu.mem_len.w) + vm->visu.mem_len.w * 0.1;
		start_y = vm->visu.memory_coord.y + (n / m) * (vm->visu.mem_len.h);
		coord.y = start_y + vm->visu.mem_len.h / 2
			- vm->visu.hex[vm->arena.mem[n] / 16]->h / 2;
		coord.x = start_x + ((vm->visu.mem_len.w * 0.8) / 4)
			- vm->visu.hex[vm->arena.mem[n] / 16]->w / 2;
		SDL_BlitSurface(vm->visu.hex[vm->arena.mem[n] / 16], NULL,
				vm->visu.window_surface, &coord);
		coord.x = start_x + ((vm->visu.mem_len.w * 0.8) * 3) / 4
			- vm->visu.hex[vm->arena.mem[n] % 16]->w / 2;
		SDL_BlitSurface(vm->visu.hex[vm->arena.mem[n] % 16],
				NULL, vm->visu.window_surface, &coord);
	}
}

static void	print_champ(t_vm *vm, SDL_Rect coord, int n)
{
	SDL_Rect printed;

	if (vm->arena.processes[n] >= 100 && vm->arena.champs[n])
	{
		coord.x += vm->visu.mem_len.w / 2
			- vm->visu.champ[vm->arena.champs[n] - 1]->w / 2;
		coord.y += vm->visu.mem_len.h / 2
			- vm->visu.champ[vm->arena.champs[n] - 1]->h / 2;
		SDL_BlitSurface(vm->visu.champ[vm->arena.champs[n] - 1], 0,
				vm->visu.window_surface, &coord);
	}
	else if (vm->arena.processes[n] < 100)
	{
		ft_bzero(&printed, sizeof(SDL_Rect));
		coord.x += vm->visu.mem_len.w / 2 - vm->visu.process->w / 2;
		coord.y += vm->visu.mem_len.h / 2 - vm->visu.process->h / 2;
		printed.w = vm->visu.process->w - (((vm->visu.mem_len.w * 0.8) *
					vm->arena.processes[n]) / 100);
		if (vm->arena.processes[n])
			printed.w -= (vm->visu.process->w - vm->visu.mem_len.w * 0.8) / 2;
		printed.h = vm->visu.process->h;
		SDL_BlitSurface(vm->visu.process, &printed, vm->visu.window_surface,
				&coord);
	}
}

void		print_memory(t_vm *vm)
{
	int			m;
	int			n;
	SDL_Rect	coord;
	SDL_Rect	printed;

	m = ft_sqrt(MEM_SIZE);
	n = -1;
	SDL_BlitSurface(vm->visu.arena, 0, vm->visu.window_surface, &vm->visu.arena_coord);
	ft_bzero(&printed, sizeof(SDL_Rect));
	while (++n < MEM_SIZE)
	{
		coord.x = vm->visu.memory_coord.x + (n % m) * (vm->visu.mem_len.w);
		coord.y = vm->visu.memory_coord.y + (n / m) * (vm->visu.mem_len.h);
		print_champ(vm, coord, n);
		print_number(vm, n, m);
	}
}
