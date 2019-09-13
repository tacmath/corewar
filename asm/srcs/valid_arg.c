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

int		label_exist(char *label, t_label *labels)
{
	int i;

	i = 0;
	while (labels[i].label)
	{
		if (!ft_strcmp(label, labels[i].label))
			return (1);
		i++;
	}
	return (0);
}

char	*valid_arg_register(t_arg_type *arg)
{
	int	i;
	int	nb;

	i = 1;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]) && i > 1)
			return (WRONG_FORMAT);
		i++;
	}
	if (i == 1)
		return (WRONG_FORMAT);
	nb = ft_atoi(arg + 1);
	if (nb > REG_NUMBER || nb == 0)
		return (WRONG_FORMAT);
	return (NULL);
}

char	*valid_arg_direct(t_arg_type *arg, t_label *labels)
{
	int i;
	int temp;

	i = 1;
	if (arg[1] == LABEL_CHAR)
	{
		if (!label_exist(arg + 2, labels))
			return (LABEL_NDEF);
	}
	else
	{
		if (arg[1] == '-')
			i++;
		temp = i;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				return (WRONG_FORMAT);
			i++;
		}
		if (i == temp)
			return (WRONG_FORMAT);
	}
	return (NULL);
}

char	*valid_arg_indirect(t_arg_type *arg, t_label *labels)
{
	int i;
	int temp;

	i = 0;
	if (arg[0] == LABEL_CHAR)
	{
		if (!label_exist(arg + 1, labels))
			return (LABEL_NDEF);
	}
	else
	{
		if (arg[0] == '-')
			i++;
		temp = i;
		while (arg[i])
		{
			if (!ft_isdigit(arg[i]))
				return (WRONG_FORMAT);
			i++;
		}
		if (i == temp)
			return (WRONG_FORMAT);
	}
	return (NULL);
}

char	*valid_arg(t_arg_type *arg, t_label *labels)
{
	char	*error;

	if (arg[0] == 'r')
	{
		if ((error = valid_arg_register(arg)))
			return (error);
	}
	else if (arg[0] == DIRECT_CHAR)
	{
		if ((error = valid_arg_direct(arg, labels)))
			return (error);
	}
	else if ((error = valid_arg_indirect(arg, labels)))
		return (error);
	return (NULL);
}
