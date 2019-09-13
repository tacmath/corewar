/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_instr.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:04:48 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:07:05 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	print_instr2(int *old_mem, int *old_pos)
{
	*old_pos = -1;
	*old_mem = -1;
	return (1);
}

static int	print_instr3(t_vm *vm)
{
	print_cycle(vm);
	SDL_UpdateWindowSurface(vm->visu.window);
	return (1);
}

static void	print_instr4(SDL_Rect *coord, t_instr_v instr, t_vm *vm, int r)
{
	*coord = treat_coord(vm, (instr.beg % r) * vm->visu.mem_len.w +
			vm->visu.memory_coord.x, (instr.beg / r) * vm->visu.mem_len.h +
			vm->visu.memory_coord.y, instr.nb_args + 3);
	print_info_mem(vm, *coord, instr);
	print_cycle(vm);
	SDL_UpdateWindowSurface(vm->visu.window);
}

int			print_instr(t_vm *vm, int mem, int status)
{
	t_instr_v	instr;
	SDL_Rect	coord;
	int			r;
	static int	old_mem = -1;
	static int	old_pos = -1;

	if (status && print_instr2(&old_mem, &old_pos))
		return (1);
	if (mem == old_mem && old_mem != -1)
		return (1);
	else
		old_mem = mem;
	r = ft_sqrt(MEM_SIZE);
	print_memory(vm);
	instr = get_instr_info(mem, vm);
	if (!instr.valid && print_instr3(vm))
		return (1);
	highlight_mem(vm, instr.beg, instr.size);
	if (instr.beg == old_pos && old_pos != -1)
		return (1);
	else
		old_pos = instr.beg;
	print_instr4(&coord, instr, vm, r);
	return (1);
}
