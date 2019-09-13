/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_ldi.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:04:16 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/28 16:51:26 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void	ldi_arg_handler(t_instr_vars *vars)
{
	if (((vars->ocp >> 6) & 0b11) != 0b01)
	{
		mem_swap(&vars->f_args[0], 2);
		vars->f_args[0] = (int16_t)vars->f_args[0];
	}
	else
		mem_swap(&vars->f_args[0], 4);
	if (((vars->ocp >> 4) & 0b11) != 0b01)
	{
		mem_swap(&vars->f_args[1], 2);
		vars->f_args[1] = (int16_t)vars->f_args[1];
	}
	else
		mem_swap(&vars->f_args[1], 4);
}

void		ldi(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	int32_t			sum;
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b110, IDX_MOD, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	if (is_reg(vars.f_args[2]))
	{
		ldi_arg_handler(&vars);
		sum = vars.f_args[0] + vars.f_args[1];
		memload(&pro->regs[vars.f_args[2] - 1], ar->mem,
				REG_SIZE, get_mempos(pro->pc + sum % IDX_MOD));
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		lldi(t_process *pro, t_arena *ar, t_instr_ret *ret, char optverbose)
{
	int32_t			sum;
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b110, 0, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	if (is_reg(vars.f_args[2]))
	{
		ldi_arg_handler(&vars);
		sum = vars.f_args[0] + vars.f_args[1];
		memload(&pro->regs[vars.f_args[2] - 1],
				ar->mem, REG_SIZE, get_mempos(pro->pc + sum));
		pro->carry = pro->regs[vars.f_args[2] - 1] == 0 ? 1 : 0;
		if (optverbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		ldi_verbose(t_process *pro, t_instr_vars *vars)
{
	int sum;

	if (((vars->ocp >> 6) & 0b11) == 0b01)
		mem_swap(&vars->c_args[0], 4);
	else
	{
		mem_swap(&vars->c_args[0], 2);
		vars->c_args[0] = (int16_t)vars->c_args[0];
	}
	if (((vars->ocp >> 4) & 0b11) == 0b01)
		mem_swap(&vars->c_args[1], 4);
	else
	{
		mem_swap(&vars->c_args[1], 2);
		vars->c_args[1] = (int16_t)vars->c_args[1];
	}
	ft_printf(" %d", vars->c_args[0]);
	ft_printf(" %d", vars->c_args[1]);
	ft_printf(" r%d\n", vars->args[2]);
	sum = vars->c_args[0] + vars->c_args[1];
	ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
		vars->c_args[0], vars->c_args[1], sum, (int)(pro->pc + sum % IDX_MOD));
}

void		lldi_verbose(t_process *pro, t_instr_vars *vars)
{
	int sum;

	if (((vars->ocp >> 6) & 0b11) == 0b01)
		mem_swap(&vars->c_args[0], 4);
	else
	{
		mem_swap(&vars->c_args[0], 2);
		vars->c_args[0] = (int16_t)vars->c_args[0];
	}
	if (((vars->ocp >> 4) & 0b11) == 0b01)
		mem_swap(&vars->c_args[1], 4);
	else
	{
		mem_swap(&vars->c_args[1], 2);
		vars->c_args[1] = (int16_t)vars->c_args[1];
	}
	ft_printf(" %d", vars->c_args[0]);
	ft_printf(" %d", vars->c_args[1]);
	ft_printf(" r%d\n", vars->args[2]);
	sum = vars->c_args[0] + vars->c_args[1];
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
			vars->c_args[0], vars->c_args[1], sum, (int)(pro->pc + sum));
}
