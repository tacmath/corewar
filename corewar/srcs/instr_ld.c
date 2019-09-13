/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_ld.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:49:58 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 21:50:00 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		ld(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b100, IDX_MOD, 4);
	get_args(pro, ar, &vars);
	if (is_reg(vars.f_args[1]))
	{
		pro->regs[vars.f_args[1] - 1] = vars.f_args[0];
		pro->carry = vars.f_args[0] == 0 ? 1 : 0;
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		lld(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b100, 0, 2);
	get_args(pro, ar, &vars);
	if (is_reg(vars.f_args[1]))
	{
		pro->regs[vars.f_args[1] - 1] = vars.f_args[0];
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		ld_verbose(t_instr_vars *vars)
{
	mem_swap(&vars->c_args[0], 4);
	ft_printf(" %d", vars->c_args[0]);
	ft_printf(" r%d\n", vars->args[1]);
}
