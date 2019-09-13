/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_live.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:47:50 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 21:47:52 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

void		live(t_process *pro, t_arena *ar, t_instr_ret *ret, char optverbose)
{
	t_instr_vars	vars;

	get_infos(pro, ar, &vars);
	set_vars(&vars, 0b100, IDX_MOD, 4);
	get_args(pro, ar, &vars);
	ret->code = 0x01;
	mem_swap(&vars.f_args[0], 4);
	ret->data = vars.f_args[0];
	if (optverbose)
		verbose(pro, &vars);
}
