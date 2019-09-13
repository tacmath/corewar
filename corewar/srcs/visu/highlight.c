/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   highlight.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:08:27 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:10:02 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	highlight_mem2(t_vm *vm, int mem, int m, SDL_Rect *coord)
{
	coord->x = vm->visu.memory_coord.x + (mem % m) * vm->visu.mem_len.w +
		vm->visu.mem_len.w / 2 - vm->visu.highlight->w / 2;
	coord->y = vm->visu.memory_coord.y + (mem / m) * vm->visu.mem_len.h +
		vm->visu.mem_len.h / 2 - vm->visu.highlight->h / 2;
	SDL_BlitSurface(vm->visu.highlight, NULL, vm->visu.window_surface, coord);
	coord->y = vm->visu.memory_coord.y + (mem / m) * vm->visu.mem_len.h +
		vm->visu.mem_len.h / 2 - vm->visu.hex[vm->arena.mem[mem] / 16]->h / 2;
	coord->x = vm->visu.memory_coord.x + (mem % m) * vm->visu.mem_len.w +
		vm->visu.mem_len.w * 0.1 + ((vm->visu.mem_len.w * 0.8) / 4) -
		vm->visu.hex[vm->arena.mem[mem] / 16]->w / 2;
	SDL_BlitSurface(vm->visu.hex[vm->arena.mem[mem] / 16],
			NULL, vm->visu.window_surface, coord);
	coord->x = vm->visu.memory_coord.x + (mem % m) * vm->visu.mem_len.w +
		vm->visu.mem_len.w * 0.1 + ((vm->visu.mem_len.w * 0.8) * 3) / 4 -
		vm->visu.hex[vm->arena.mem[mem] % 16]->w / 2;
	SDL_BlitSurface(vm->visu.hex[vm->arena.mem[mem] % 16],
			NULL, vm->visu.window_surface, coord);
}

int			highlight_mem(t_vm *vm, int start, int len)
{
	int			mem;
	int			m;
	SDL_Rect	coord;

	m = ft_sqrt(MEM_SIZE);
	mem = start - 1;
	len += start;
	while (++mem < len)
		highlight_mem2(vm, mem, m, &coord);
	return (1);
}
