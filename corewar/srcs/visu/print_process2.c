/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_process2.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:20:06 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:25:22 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		get_max_process_num(t_process **process)
{
	int n;

	n = -1;
	while (process[++n])
		;
	return (n);
}

int		print_process_1(t_process ***process, int *process_num,
		int *old_mem)
{
	free(*process);
	*process = 0;
	*process_num = 0;
	*old_mem = -1;
	return (1);
}
