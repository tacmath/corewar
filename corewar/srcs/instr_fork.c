/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_fork.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:09:08 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 22:09:09 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		fork_i(t_process *pro, t_arena *ar, t_instr_ret *ret,
			char option_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b000, IDX_MOD, 4);
	get_args(pro, ar, &vars);
	mem_swap(vars.f_args, 2);
	ret->data = get_mempos(pro->pc + ((int16_t)vars.f_args[0] % IDX_MOD));
	ret->code = 0x0c;
	if (option_verbose)
		verbose(pro, &vars);
}

void		lfork(t_process *pro, t_arena *ar, t_instr_ret *ret,
			char option_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b000, 0, 4);
	get_args(pro, ar, &vars);
	mem_swap(vars.f_args, 2);
	ret->data = get_mempos(pro->pc + (int16_t)vars.f_args[0]);
	ret->code = 0x0f;
	if (option_verbose)
		verbose(pro, &vars);
}

void		fork_verbose(t_process *pro, t_instr_vars *vars)
{
	ft_printf(" %d", (int16_t)vars->f_args[0]);
	ft_printf(" (%d)\n", pro->pc + (int16_t)vars->f_args[0] % IDX_MOD);
}

void		lfork_verbose(t_process *pro, t_instr_vars *vars)
{
	ft_printf(" %d", (int16_t)vars->f_args[0]);
	ft_printf(" (%d)\n", pro->pc + (int16_t)vars->f_args[0]);
}
