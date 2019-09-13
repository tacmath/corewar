/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:39:17 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 15:26:35 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void		get_instr_info2(t_vm *vm, t_instr_v *ret, int i)
{
	ret->beg = i;
	ret->instr = vm->arena.mem[i];
	ret->size = 1;
	ret->ocp = 0;
	ret->valid = 0;
}

void		get_instr_info3(t_vm *vm, t_instr_v *ret, int i)
{
	int	size_args;

	ret->ocp = (char)vm->arena.mem[(i + 1) % MEM_SIZE];
	size_args = get_size_args(ret->ocp, search_op(ret->instr));
	ret->valid = size_args <= 0 ? 0 : 1;
	size_args = size_args < 0 ? -size_args : size_args;
	ret->size = 2 + size_args;
}

t_instr_v	get_instr_info(int16_t mem, t_vm *vm)
{
	t_instr_v	ret;
	int			i;

	i = 0;
	while (i < MEM_SIZE)
	{
		get_instr_info2(vm, &ret, i);
		if (ret.instr > 0 && ret.instr <= NB_OPS && (ret.valid = 1))
		{
			if (is_instr_without_ocp(ret.instr))
				ret.size = 1 + g_op_tab[(int)ret.instr - 1].dir_size;
			else
				get_instr_info3(vm, &ret, i);
		}
		if (mem >= i && mem < i + ret.size)
		{
			ret.ocp = is_instr_without_ocp(
			ret.instr) ? -1 : vm->arena.mem[(i + 1 % MEM_SIZE)];
			return (complete_instr(vm, &ret));
		}
		i += ret.size;
	}
	ret.instr = -1;
	return (ret);
}
