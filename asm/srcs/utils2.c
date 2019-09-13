/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   spec_atoi.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: krambono <krambono@student.le-101.f>       +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/14 09:46:34 by krambono     #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 13:40:58 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

t_arg_type	get_arg_type(t_arg_type *arg)
{
	if (arg[0] == 'r')
		return (T_REG);
	if (arg[0] == '%')
		return (T_DIR);
	return (T_IND);
}

char		get_arg_code(t_arg_type *arg)
{
	if (arg[0] == 'r')
		return (0b01);
	if (arg[0] == '%')
		return (0b10);
	return (0b11);
}

int			search_op(char *command)
{
	int i;

	i = 0;
	while (i < NB_OPS)
	{
		if (command[0] && !ft_strcmp(g_op_tab[i].name, command))
			return (i);
		i++;
	}
	return (-1);
}
