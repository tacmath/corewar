/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   process_list.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/29 14:05:13 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 14:31:11 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

t_process_list	*create_process_list(void)
{
	t_process_list *list;

	if (!(list = (t_process_list *)ft_memalloc(sizeof(t_process_list))))
		return (error_null(ALLOC_FAILED));
	list->next = NULL;
	return (list);
}

int				add_process(t_process_list **list)
{
	t_process_list *new_list;

	if (!(new_list = create_process_list()))
		return (error_int(ALLOC_FAILED));
	new_list->next = *list;
	*list = new_list;
	return (1);
}

void			clear_process_list(t_process_list **list)
{
	t_process_list *temp;

	while (*list)
	{
		temp = (*list)->next;
		free(*list);
		*list = temp;
	}
}

void			init_process(t_process *process, uint32_t id, int pc, int num)
{
	int32_t champ_id;

	champ_id = id;
	process->champ_id = champ_id;
	process->pc = pc;
	process->num = num;
	process->carry = 0;
	champ_id = UINT32_MAX - champ_id + 1;
	mem_swap(&champ_id, 4);
	process->regs[0] = champ_id;
	process->cycles_left = -1;
	process->op = -1;
	process->live = 0;
	process->cycle_last_live = 0;
}

t_process_list	*init_process_list(t_champ_decoded *champs_decoded,
				int nb_champs)
{
	t_process_list	*list;
	int				i;

	i = 0;
	list = NULL;
	while (i < nb_champs)
	{
		if (!add_process(&list))
		{
			clear_process_list(&list);
			return (error_null(ALLOC_FAILED));
		}
		init_process(&list->process, champs_decoded[i].id,
		champs_decoded[i].start, i + 1);
		list->process.visu_id = champs_decoded[i].visu_id;
		i++;
	}
	return (list);
}
