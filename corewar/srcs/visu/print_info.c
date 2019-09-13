/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_info.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:00:41 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:03:31 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	print_info2(t_vm *vm)
{
	print_process(vm, 0, RESET);
	print_instr(vm, 0, RESET);
	print_memory(vm);
	print_cycle(vm);
	SDL_UpdateWindowSurface(vm->visu.window);
	return (1);
}

static int	print_info3(t_vm *vm, int mem)
{
	print_process(vm, 0, RESET);
	if (vm->arena.champs[mem] == 0)
	{
		print_instr(vm, 0, RESET);
		print_memory(vm);
		print_cycle(vm);
		SDL_UpdateWindowSurface(vm->visu.window);
	}
	else if (!print_instr(vm, mem, PRINT))
		return (0);
	return (1);
}

int			print_info(t_vm *vm, int x, int y)
{
	int	mem;

	x -= vm->visu.memory_coord.x;
	y -= vm->visu.memory_coord.y;
	mem = (y / vm->visu.mem_len.h) * ft_sqrt(MEM_SIZE);
	mem += (x / vm->visu.mem_len.w);
	if ((mem < 0 || mem >= MEM_SIZE || x >= vm->visu.memory_coord.w
				|| x < 0 || y < 0) && print_info2(vm))
		return (1);
	if (vm->arena.processes[mem] <= 100)
	{
		print_instr(vm, 0, RESET);
		if (!print_process(vm, mem, PRINT))
			return (0);
	}
	else if (print_info3(vm, mem))
		return (0);
	return (1);
}
