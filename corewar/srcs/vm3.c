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

int		get_size_args(char ocp, int index_op)
{
	int		size;
	int		i;
	int		error;
	char	nb;

	error = 0;
	size = 0;
	i = 0;
	while (i < g_op_tab[index_op].nb_arg)
	{
		nb = (ocp >> ((3 - i) * 2)) & 0b11;
		if (((pow2(nb - 1) & g_op_tab[index_op].arg[i]) == 0) || nb == 0)
			error = 1;
		if (nb == 0b01)
			size += 1;
		if (nb == 0b11)
			size += 2;
		if (nb == 0b10)
			size += g_op_tab[index_op].dir_size == 2 ? 2 : 4;
		i++;
	}
	return (error ? -1 * size : size);
}

void	reset_instr_ret(t_instr_ret *ret)
{
	ret->code = -1;
	ret->data = 0;
	ft_bzero(ret->args, sizeof(int32_t[3]));
}

void	execute_instr2(t_vm *vm, t_process *process,
		t_instr_ret *instr_ret, int *size_instr)
{
	int index_op;
	int	size_args;

	index_op = search_op(process->op);
	if (is_instr_without_ocp(process->op))
	{
		*size_instr = g_op_tab[index_op].dir_size + 1;
		g_instrs_f[process->op - 1](process, &vm->arena, instr_ret,
		vm->options.verbose);
		process->pc = (process->pc + *size_instr) % MEM_SIZE;
	}
	else
	{
		size_args = get_size_args(*(vm->arena.mem +
		(process->pc + 1) % MEM_SIZE), index_op);
		*size_instr = (size_args < 0 ? -size_args : size_args) + 1 + 1;
		if (size_args > 0)
			g_instrs_f[process->op - 1](process, &vm->arena, instr_ret,
			vm->options.verbose);
		process->pc = (process->pc + *size_instr) % MEM_SIZE;
	}
}

int		execute_instr(t_vm *vm, t_process *process)
{
	int			size_instr;
	int			old_pc;
	t_instr_ret	instr_ret;

	old_pc = process->pc;
	reset_instr_ret(&instr_ret);
	execute_instr2(vm, process, &instr_ret, &size_instr);
	if (instr_ret.code != -1)
		if (!ret_instr(vm, &instr_ret, process))
			return (0);
	if (vm->options.verbose && !(process->op == 9 && process->carry == 1))
		print_adv(size_instr, vm->arena.mem, old_pc);
	return (1);
}
