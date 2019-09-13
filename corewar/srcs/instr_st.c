/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_st.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:52:54 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 21:52:56 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		st(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b100, IDX_MOD, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	if ((vars.ocp & 0x30) == 0x30)
	{
		mem_swap(&vars.f_args[1], IND_SIZE);
		memstore(ar->mem, &vars.f_args[0], REG_SIZE, get_mempos(pro->pc +
					((int16_t)vars.f_args[1] % IDX_MOD)));
		memsetcir(ar->champs, pro->visu_id, REG_SIZE, get_mempos(pro->pc +
					((int16_t)vars.f_args[1] % IDX_MOD)));
		if (opt_verbose)
			verbose(pro, &vars);
	}
	else if (is_reg(vars.f_args[1]))
	{
		pro->regs[vars.f_args[1] - 1] = vars.f_args[0];
		if (opt_verbose)
			verbose(pro, &vars);
	}
	ret->code = -1;
}

void		st_verbose(t_instr_vars *vars)
{
	ft_printf(" r%d", vars->args[0]);
	if (((vars->ocp >> 4) & 0b11) == 0b11)
	{
		mem_swap(&vars->args[1], 2);
		vars->args[1] = (int16_t)vars->args[1];
	}
	ft_printf(" %d\n", vars->args[1]);
}
