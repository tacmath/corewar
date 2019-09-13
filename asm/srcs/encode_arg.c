/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: krambono <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 15:20:10 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 16:09:06 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

void	encode_arg_indirect(t_arg_type *arg, t_arg_encoded *arg_encoded)
{
	if (arg[0] == LABEL_CHAR)
		arg_encoded->arg = 0;
	else
	{
		if (arg[0] != '-')
			arg_encoded->arg = ft_atoi(arg);
		else
			arg_encoded->arg = ~(uint16_t)(ft_atoi(arg + 1)) + 1;
	}
}

void	encode_arg_direct(t_arg_type *arg, t_arg_encoded *arg_encoded)
{
	if (arg[1] == LABEL_CHAR)
		arg_encoded->arg = 0;
	else
	{
		if (arg[1] != '-')
			arg_encoded->arg = ft_atoi(arg + 1);
		else
		{
			if (arg_encoded->nb_bytes == 2)
				arg_encoded->arg = ~(uint16_t)(ft_atoi(arg + 2)) + 1;
			else
				arg_encoded->arg = ~(uint32_t)(ft_atoi(arg + 2)) + 1;
		}
	}
}

void	encode_arg(t_arg_type *arg, t_arg_encoded *arg_encoded)
{
	t_arg_type	arg_type;

	arg_type = get_arg_type(arg);
	if (arg_type == T_REG)
		arg_encoded->arg = ft_atoi(arg + 1);
	else if (arg_type == T_IND)
		encode_arg_indirect(arg, arg_encoded);
	else
		encode_arg_direct(arg, arg_encoded);
}
