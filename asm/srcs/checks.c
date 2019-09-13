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

int		check_args(t_instr instr, t_label *labels)
{
	int		i;
	int		selected_op;
	char	*error;

	selected_op = search_op(instr.command);
	i = 0;
	while (i < MAX_ARGS_NUMBER && instr.args[i])
	{
		if (i >= g_op_tab[selected_op].nb_arg)
			return (!ft_dprintf(2, MANY_ARGS, instr.line));
		if ((get_arg_type(instr.args[i]) & g_op_tab[selected_op].arg[i]) == 0)
			return (!ft_dprintf(2, WRONG_TYPE, instr.line));
		if ((error = valid_arg(instr.args[i], labels)))
			return (!ft_dprintf(2, error, instr.line));
		i++;
	}
	if (i <= 2 && g_op_tab[selected_op].arg[i])
	{
		return (!ft_dprintf(2, "Error line %d : not enough arguments\n",
		instr.line));
	}
	return (1);
}

int		check_instrs(t_instr *instrs, int nb_instrs, t_label *labels)
{
	int i;

	i = 0;
	while (i < nb_instrs)
	{
		if (!check_command(instrs[i]))
			return (0);
		if (!check_args(instrs[i], labels))
			return (0);
		i++;
	}
	return (1);
}

int		check_command(t_instr instr)
{
	int i;

	i = 0;
	while (i < NB_OPS)
	{
		if (!ft_strcmp(instr.command, g_op_tab[i].name))
			return (1);
		i++;
	}
	return (!ft_dprintf(2, "Error line %d : invalid instruction\n",
	instr.line));
}
