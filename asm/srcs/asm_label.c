/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm_label.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 14:06:01 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 13:31:39 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		handle_pos(t_asm *sam)
{
	int				i;
	char			opcode;
	int				j;
	int				k;

	i = -1;
	k = 0;
	sam->size = 0;
	while (sam && ++i < sam->nb_instrs)
	{
		sam->instrs[i].pos = sam->size;
		while (sam->labels[k].label != NULL && i == sam->labels[k].pos)
			sam->labels[k++].pos_oct = sam->size;
		(sam->size)++;
		opcode = sam->instrs_asm[i].op_code;
		if (!(opcode == 1 || opcode == 9 || opcode == 12 || opcode == 15))
			(sam->size)++;
		j = -1;
		while (++j < sam->instrs[i].nb_arg)
			(sam->size) += sam->instrs_asm[i].op_args[j].nb_bytes;
	}
	while (sam->labels[k].label != NULL)
		sam->labels[k++].pos_oct = sam->size;
	return (*(int*)mem_swap(&sam->size, sizeof(sam->size)));
}
