/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_aff.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:10:40 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 22:10:42 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		aff(t_process *pro, t_arena *ar, t_instr_ret *ret, char opt_verbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b100, 0, 4);
	if (!get_args(pro, ar, &vars))
		return ;
	mem_swap(&vars.f_args[0], 4);
	ret->data = vars.f_args[0] % 256;
	ret->code = 0x10;
	opt_verbose = 0;
}
