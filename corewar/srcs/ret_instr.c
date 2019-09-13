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

void	ret_live(t_vm *vm, t_instr_ret *instr_ret, t_process *process)
{
	int index_player;

	process->live = 1;
	process->cycle_last_live = vm->cycle;
	index_player = search_champ(vm->options.num_champs, vm->nb_champs,
	(uint32_t)(UINT32_MAX - instr_ret->data + 1));
	if (index_player != -1)
	{
		vm->last_live = index_player;
		vm->live_champs[index_player]++;
		if (vm->options.verbose)
			ft_printf("Player %d (%s) is said to be alive\n",
			vm->champs_decoded[vm->last_live].id,
			vm->champs_decoded[vm->last_live].header.prog_name);
	}
	vm->nb_live++;
}

void	ret_zjmp(t_vm *vm, t_instr_ret *instr_ret, t_process *process)
{
	vm->arena.processes[instr_ret->data] = 1;
	process->pc = instr_ret->data;
}

int		ret_fork(t_vm *vm, t_instr_ret *instr_ret, t_process *process)
{
	if (!add_process(&(vm->list)))
		return (0);
	vm->list->process = *process;
	vm->list->process.pc = instr_ret->data;
	vm->list->process.cycles_left = -1;
	vm->list->process.num = ++vm->num_procs;
	vm->nb_procs++;
	return (1);
}

void	ret_aff(t_vm *vm, t_instr_ret *instr_ret)
{
	if (vm->options.cycle_dump == -1 && !vm->options.verbose
		&& vm->options.visu)
		ft_putchar((char)instr_ret->data);
}

int		ret_instr(t_vm *vm, t_instr_ret *instr_ret, t_process *process)
{
	if (instr_ret->code == 0x01)
		ret_live(vm, instr_ret, process);
	else if (instr_ret->code == 0x09)
		ret_zjmp(vm, instr_ret, process);
	else if (instr_ret->code == 0x0C || instr_ret->code == 0x0F)
	{
		if (!ret_fork(vm, instr_ret, process))
			return (0);
	}
	else if (instr_ret->code == 0x10)
		ret_aff(vm, instr_ret);
	return (1);
}
