/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_args.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:34:59 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/28 17:29:25 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static	int	get_size_aargs(t_instr_vars *vars, int i)
{
	char	nb;

	nb = (vars->ocp >> ((3 - i) * 2)) & 0b11;
	if (nb == 0)
		return (0);
	if (nb == REG_CODE)
		return (1);
	else if (nb == IND_CODE)
		return (2);
	else
		return (g_op_tab[vars->index_op].dir_size);
}

static int	no_ocp_instr(t_process *pro, t_instr_vars *vars, t_arena *ar)
{
	memload(vars->args, ar->mem, g_op_tab[vars->index_op].dir_size,
	get_mempos(pro->pc + 1));
	vars->f_args[0] = vars->args[0];
	vars->c_args[0] = vars->f_args[0];
	return (1);
}

static int	transform(t_process *pro, t_arena *ar, t_instr_vars *vars, int i)
{
	char	nb;
	int16_t	temp;

	nb = (vars->ocp >> ((3 - i) * 2)) & 0b11;
	if (nb == REG_CODE)
	{
		if (!is_reg(vars->args[i]))
			return (0);
		vars->f_args[i] = pro->regs[vars->args[i] - 1];
	}
	else if (nb == IND_CODE)
	{
		temp = vars->args[i];
		mem_swap(&temp, 2);
		memload(&vars->f_args[i], ar->mem, vars->ind_size, get_mempos(pro->pc +
		(vars->idx ? (int16_t)temp % vars->idx : (int16_t)temp)));
	}
	else
		vars->f_args[i] = vars->args[i];
	return (1);
}

int			get_args(t_process *pro, t_arena *ar, t_instr_vars *vars)
{
	int		i;
	char	delta;
	char	size;

	if (vars->op == 1 || vars->op == 9 || vars->op == 12 || vars->op == 15)
		return (no_ocp_instr(pro, vars, ar));
	i = -1;
	delta = 0;
	while (++i < g_op_tab[vars->index_op].nb_arg)
	{
		if (!(size = get_size_aargs(vars, i)))
			break ;
		memload(&vars->args[i], ar->mem, size, get_mempos(pro->pc + delta + 2));
		if ((vars->transform >> (2 - i)) & 1)
		{
			if (!transform(pro, ar, vars, i))
				return (0);
		}
		else
			vars->f_args[i] = vars->args[i];
		vars->c_args[i] = vars->f_args[i];
		delta += size;
	}
	return (1);
}

void		set_vars(t_instr_vars *vars, char transform, int idx, char ind_size)
{
	vars->transform = transform;
	vars->idx = idx;
	vars->ind_size = ind_size;
}
