/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_zjmp.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:02:09 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 22:02:12 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		zjmp(t_process *pro, t_arena *ar, t_instr_ret *ret, char optverbose)
{
	t_instr_vars vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b000, 0, 2);
	get_args(pro, ar, &vars);
	if (pro->carry == 1)
	{
		mem_swap(&(vars.f_args[0]), 2);
		ret->code = 0x09;
		ret->data = get_mempos(pro->pc + (int16_t)vars.f_args[0] % IDX_MOD);
	}
	if (optverbose)
		verbose(pro, &vars);
}

void		zjmp_verbose(t_process *pro, t_instr_vars *vars)
{
	mem_swap(vars->c_args, 2);
	ft_printf(" %d", (int16_t)vars->c_args[0]);
	ft_printf(pro->carry == 1 ? " OK\n" : " FAILED\n");
}
