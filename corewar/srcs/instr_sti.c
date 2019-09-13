/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_sti.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:07:19 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/28 16:54:42 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	sti_arg_handler(t_instr_vars *vars)
{
	if (((vars->ocp >> 4) & 0b11) == 0b01 || ((vars->ocp >> 4) & 0b11) == 0b11)
		mem_swap(&vars->f_args[1], 4);
	else
	{
		mem_swap(&vars->f_args[1], 2);
		vars->f_args[1] = (int16_t)vars->f_args[1];
	}
	if (((vars->ocp >> 2) & 0b11) == 0b01 || ((vars->ocp >> 2) & 0b11) == 0b11)
		mem_swap(&vars->f_args[2], 4);
	else
	{
		mem_swap(&vars->f_args[2], 2);
		vars->f_args[2] = (int16_t)vars->f_args[2];
	}
}

void		sti(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	int32_t			pos;
	int32_t			sum;
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b111, IDX_MOD, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	sti_arg_handler(&vars);
	sum = vars.f_args[1] + vars.f_args[2];
	pos = get_mempos(pro->pc + sum % IDX_MOD);
	memstore(ar->mem, &vars.f_args[0], REG_SIZE, pos);
	memsetcir(ar->champs, pro->visu_id, REG_SIZE, pos);
	ret->code = -1;
	if (opt_verbose)
		verbose(pro, &vars);
}

void		sti_verbose(t_process *pro, t_instr_vars *vars)
{
	int sum;

	ft_printf(" r%d", vars->args[0]);
	if (((vars->ocp >> 4) & 0b11) == 0b01 || ((vars->ocp >> 4) & 0b11) == 0b11)
		mem_swap(&vars->c_args[1], 4);
	else
	{
		mem_swap(&vars->c_args[1], 2);
		vars->c_args[1] = (int16_t)vars->c_args[1];
	}
	if (((vars->ocp >> 2) & 0b11) == 0b01 || ((vars->ocp >> 2) & 0b11) == 0b11)
		mem_swap(&vars->c_args[2], 4);
	else
	{
		mem_swap(&vars->c_args[2], 2);
		vars->c_args[2] = (int16_t)vars->c_args[2];
	}
	ft_printf(" %d", vars->c_args[1]);
	ft_printf(" %d\n", vars->c_args[2]);
	sum = vars->c_args[1] + vars->c_args[2];
	ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		vars->c_args[1], vars->c_args[2], sum, (int)(pro->pc + sum % IDX_MOD));
}
