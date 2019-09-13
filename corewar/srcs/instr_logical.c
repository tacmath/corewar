/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_logical.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:59:36 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 21:59:39 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		and(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b110, IDX_MOD, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	if (is_reg(vars.f_args[2]))
	{
		pro->regs[vars.f_args[2] - 1] = vars.f_args[0] & vars.f_args[1];
		pro->carry = pro->regs[vars.f_args[2] - 1] == 0 ? 1 : 0;
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		or(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b110, IDX_MOD, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	if (is_reg(vars.f_args[2]))
	{
		pro->regs[vars.f_args[2] - 1] = vars.f_args[0] | vars.f_args[1];
		pro->carry = pro->regs[vars.f_args[2] - 1] == 0 ? 1 : 0;
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		xor(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b110, IDX_MOD, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	if (is_reg(vars.f_args[2]))
	{
		pro->regs[vars.f_args[2] - 1] = vars.f_args[0] ^ vars.f_args[1];
		pro->carry = pro->regs[vars.f_args[2] - 1] == 0 ? 1 : 0;
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		logical_verbose(t_instr_vars *vars)
{
	mem_swap(&vars->c_args[0], 4);
	mem_swap(&vars->c_args[1], 4);
	ft_printf(" %d", vars->c_args[0]);
	ft_printf(" %d", vars->c_args[1]);
	ft_printf(" r%d\n", vars->args[2]);
}
