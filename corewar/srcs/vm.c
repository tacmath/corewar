/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:39:17 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/11 15:12:46 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	arena_processes(t_vm *vm, t_process *process)
{
	if (process->op != -1)
		vm->arena.processes[process->pc] = (process->cycles_left /
		(double)g_op_tab[search_op(process->op)].nb_cycles) * 100;
	else
		vm->arena.processes[process->pc] = 0;
}

int		browse_processes(t_vm *vm)
{
	t_process_list	*temp;

	temp = vm->list;
	while (temp)
	{
		if (temp->process.cycles_left == 0)
		{
			vm->arena.processes[temp->process.pc] = -1;
			if (temp->process.op != -1)
			{
				if (!execute_instr(vm, &temp->process))
					return (0);
			}
			else
				temp->process.pc = (temp->process.pc + 1) % MEM_SIZE;
		}
		if (temp->process.cycles_left == -1)
			get_instr(vm, &temp->process);
		arena_processes(vm, &temp->process);
		temp->process.cycles_left--;
		temp = temp->next;
	}
	return (1);
}

int		corewar_loop(t_vm *vm, int *last_cycle)
{
	char check_process;

	if (vm->options.verbose)
		ft_printf("It is now cycle %d\n", vm->cycle);
	check_process = vm->cycle_to_die <= 0 || (vm->cycle - *last_cycle)
	% vm->cycle_to_die == 0;
	if (!browse_processes(vm))
		return (0);
	if (check_process)
	{
		delete_processes(vm);
		decrease_ctd(vm, last_cycle);
	}
	vm->cycle_left_to_die = vm->cycle - *last_cycle;
	if (vm->options.visu)
		print_mem(vm);
	vm->cycle++;
	return (1);
}

void	init_loop(t_vm *vm, int *last_cycle)
{
	int n;

	n = -1;
	while (++n < MEM_SIZE)
		vm->arena.processes[n] = -1;
	vm->list = NULL;
	vm->nb_procs = vm->nb_champs;
	vm->num_procs = vm->nb_champs;
	vm->nb_live = 0;
	vm->cycle = 1;
	*last_cycle = 0;
}

int		corewar(t_vm *vm)
{
	int last_cycle;

	init_loop(vm, &last_cycle);
	if (!(vm->list = init_process_list(vm->champs_decoded, vm->nb_champs)))
		return (0);
	verbose_begin(vm);
	while (vm->list)
	{
		if (vm->options.cycle_dump != -1 && vm->options.cycle_dump
			== vm->cycle - 1)
			return (memdump(vm));
		if (!corewar_loop(vm, &last_cycle))
			return (0);
	}
	verbose_end(vm);
	return (1);
}
