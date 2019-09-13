/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_utils2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:28:21 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/28 16:50:51 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int		search_op(int opcode)
{
	int i;

	i = 0;
	while (i < NB_OPS)
	{
		if (g_op_tab[i].opcode == opcode)
			return (i);
		i++;
	}
	return (-1);
}

void	get_infos(t_process *pro, t_arena *ar, t_instr_vars *vars)
{
	vars->op = pro->op;
	if (!(vars->op == 1 || vars->op == 9 || vars->op == 12 || vars->op == 15))
		vars->ocp = *(ar->mem + (pro->pc + 1) % MEM_SIZE);
	vars->index_op = search_op(vars->op);
	ft_bzero(vars->args, sizeof(int32_t[3]));
	ft_bzero(vars->f_args, sizeof(int32_t[3]));
}

int		is_reg(char nb)
{
	return (nb > 0 && nb <= REG_NUMBER);
}
