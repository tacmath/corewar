/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_addsub.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:55:00 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/28 16:49:55 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		add(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;
	int32_t			res;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b110, IDX_MOD, 2);
	if (!get_args(pro, ar, &vars))
		return ;
	if (is_reg(vars.f_args[2]))
	{
		mem_swap(&(vars.f_args[0]), 4);
		mem_swap(&(vars.f_args[1]), 4);
		res = vars.f_args[0] + vars.f_args[1];
		mem_swap(&(res), 4);
		pro->regs[vars.f_args[2] - 1] = res;
		pro->carry = res == 0 ? 1 : 0;
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		sub(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;
	int32_t			res;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b110, IDX_MOD, 2);
	if (!get_args(pro, ar, &vars))
		return ;
	if (is_reg(vars.f_args[2]))
	{
		mem_swap(&(vars.f_args[0]), 4);
		mem_swap(&(vars.f_args[1]), 4);
		res = vars.f_args[0] - vars.f_args[1];
		mem_swap(&(res), 4);
		pro->regs[vars.f_args[2] - 1] = res;
		pro->carry = res == 0 ? 1 : 0;
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}
