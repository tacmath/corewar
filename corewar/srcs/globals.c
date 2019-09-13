/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   globals.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: krambono <lperron@student.le-101.f>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/28 15:09:43 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/06 14:54:36 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	(*g_instrs_f[NB_OPS])(t_process *proc, t_arena *arena, t_instr_ret *ret,
		char verbose) =
{
	&live, &ld, &st, &add, &sub, &and, &or, &xor, &zjmp, &ldi, &sti,
	&fork_i, &lld, &lldi, &lfork, &aff
};
