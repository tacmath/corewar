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

void	decrease_ctd(t_vm *vm, int *last_cycle)
{
	static char check = 0;

	if (check >= MAX_CHECKS - 1 || vm->nb_live >= NBR_LIVE)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		if (vm->options.verbose)
			ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
		check = 0;
		*last_cycle = vm->cycle;
	}
	else
		check++;
	vm->nb_live = 0;
}

void	delete_processes(t_vm *vm)
{
	t_process_list	*temp;
	t_process_list	*prev;

	prev = NULL;
	temp = vm->list;
	while (temp)
	{
		if (temp->process.live == 0 || vm->cycle_to_die <= 0)
		{
			if (vm->options.verbose)
				ft_printf("Process %u hasn't lived for %d cycles (CTD %d)\n",
temp->process.num, vm->cycle - temp->process.cycle_last_live, vm->cycle_to_die);
			del_process_ctd(vm, &temp, &prev);
			continue ;
		}
		else
			temp->process.live = 0;
		prev = temp;
		temp = temp->next;
	}
}

void	del_process_ctd(t_vm *vm, t_process_list **temp, t_process_list **prev)
{
	vm->arena.processes[(*temp)->process.pc] = -1;
	if (*prev)
	{
		(*prev)->next = (*temp)->next;
		free(*temp);
		*temp = (*prev)->next;
	}
	else
	{
		vm->list = (*temp)->next;
		free(*temp);
		*temp = vm->list;
	}
	vm->nb_procs--;
}

void	get_instr(t_vm *vm, t_process *process)
{
	int index_op;

	index_op = search_op(*(vm->arena.mem + process->pc));
	process->op = index_op == -1 ? -1 : *(vm->arena.mem + process->pc);
	if (process->op != -1)
		process->cycles_left = g_op_tab[index_op].nb_cycles - 1;
	else
	{
		vm->arena.processes[process->pc] = -1;
		process->pc = (process->pc + 1) % MEM_SIZE;
		process->cycles_left = 0;
	}
}
