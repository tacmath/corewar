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

t_process	**get_process(int16_t mem, t_vm *vm)
{
	t_process_list	*tmp;
	t_process		**ret;
	int				i;
	int				j;

	i = 0;
	tmp = vm->list;
	while (tmp)
	{
		if (tmp->process.pc == mem)
			i++;
		tmp = tmp->next;
	}
	if (!(ret = ft_memalloc(sizeof(t_process*) * (i + 1))))
		return (NULL);
	tmp = vm->list;
	j = -1;
	while (tmp && j < i)
	{
		if (tmp->process.pc == mem)
			ret[++j] = &tmp->process;
		tmp = tmp->next;
	}
	return (ret);
}

void		get_multiple_args(t_vm *vm, t_instr_v *ret)
{
	char	type;
	int		i;
	int		size;
	int		off;

	i = -1;
	off = 0;
	while (++i < ret->nb_args)
	{
		type = (ret->ocp >> (2 * (3 - i))) & 3;
		if (type == REG_CODE)
			size = 1;
		else if (type == DIR_CODE)
			size = g_op_tab[(int)ret->instr - 1].dir_size;
		else
			size = 2;
		memload((char*)&ret->args[i], (char*)vm->arena.mem, size,
		(ret->beg + 2 + off) % MEM_SIZE);
		mem_swap(&ret->args[i], size);
		off += size;
	}
}

t_instr_v	complete_instr(t_vm *vm, t_instr_v *ret)
{
	ft_bzero(ret->args, sizeof(int) * 3);
	if (!ret->valid)
		return (*ret);
	ret->nb_args = g_op_tab[(int)ret->instr - 1].nb_arg;
	if (is_instr_without_ocp(ret->instr))
	{
		memload((char*)&ret->args[0], (char*)vm->arena.mem,
		g_op_tab[(int)ret->instr - 1].dir_size, (ret->beg + 1) % MEM_SIZE);
		mem_swap(&ret->args[0], g_op_tab[(int)ret->instr].dir_size);
		return (*ret);
	}
	get_multiple_args(vm, ret);
	return (*ret);
}
