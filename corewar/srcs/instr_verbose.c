/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_verbose.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:12:36 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 22:12:50 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		verbose(t_process *pro, t_instr_vars *vars)
{
	ft_printf("P %4d | %s", pro->num, g_op_tab[vars->index_op].name);
	if (vars->op == 0x01)
		ft_printf(" %d\n", vars->f_args[0]);
	else if (vars->op == 0x02)
		ld_verbose(vars);
	else if (vars->op == 0x03)
		st_verbose(vars);
	else if (vars->op >= 0x06 && vars->op <= 0x08)
		logical_verbose(vars);
	else if (vars->op == 0x09)
		zjmp_verbose(pro, vars);
	else if (vars->op == 0x0a)
		ldi_verbose(pro, vars);
	else if (vars->op == 0x0b)
		sti_verbose(pro, vars);
	else if (vars->op == 0x0c)
		fork_verbose(pro, vars);
	else if (vars->op == 0x0e)
		lldi_verbose(pro, vars);
	else if (vars->op == 0x0f)
		lfork_verbose(pro, vars);
	else
		generic_verbose(vars);
}

void		generic_verbose(t_instr_vars *vars)
{
	int i;
	int nb;

	i = 0;
	while (i < g_op_tab[vars->index_op].nb_arg)
	{
		nb = (vars->ocp >> ((3 - i) * 2)) & 0b11;
		if (nb == 0)
			break ;
		if (nb == 0b01)
			ft_printf(" r%d", vars->args[i]);
		else if (nb == 0b11)
		{
			mem_swap(&vars->args[i], 2);
			ft_printf(" %d", (int16_t)vars->args[i]);
		}
		else
		{
			mem_swap(&vars->args[i], g_op_tab[vars->index_op].dir_size);
			ft_printf(" %d", g_op_tab[vars->index_op].dir_size == 2 ?
					(int16_t)vars->args[i] : (int32_t)vars->args[i]);
		}
		i++;
	}
	ft_printf("\n");
}
