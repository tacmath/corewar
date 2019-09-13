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

unsigned int	pow2(char n)
{
	return (n < 0 ? 0 : 1 << n);
}

int				is_instr_without_ocp(int nb)
{
	return (nb == 1 || nb == 9 || nb == 12 || nb == 15);
}

char			*get_exec_path(char *name)
{
	int n;
	int tmp;

	n = -1;
	tmp = 0;
	while (name[++n])
		if (name[n] == '/')
			tmp = n + 1;
	name[tmp] = 0;
	return (ft_strdup(name));
}

void			clean(t_vm *vm)
{
	clear_process_list(&(vm->list));
	free_champs_decoded(vm->champs_decoded);
}

int				search_champ(uint32_t *num_champs, int nb_champs, uint32_t id)
{
	int i;

	i = 0;
	while (i < nb_champs)
	{
		if (num_champs[i] == id)
			return (i);
		i++;
	}
	return (-1);
}
