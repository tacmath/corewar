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

void	size_arg(t_arg_type *arg, t_arg_encoded *arg_encoded, int selected_op)
{
	t_arg_type	arg_type;

	arg_type = get_arg_type(arg);
	if (arg_type == T_REG)
		arg_encoded->nb_bytes = 1;
	else if (arg_type == T_IND)
		arg_encoded->nb_bytes = 2;
	else
		arg_encoded->nb_bytes = g_op_tab[selected_op].dir_size;
}

char	get_ocp(t_arg_type *args[MAX_ARGS_NUMBER], char op_code)
{
	unsigned char	ocp;
	int				i;

	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (0);
	ocp = 0;
	i = 2;
	while (i >= 0 && args[2 - i])
	{
		ocp = ocp | (get_arg_code(args[2 - i]) << ((i + 1) * 2));
		i -= 1;
	}
	return (ocp);
}

int		get_size_instrs(t_asm *sam)
{
	int i;
	int j;
	int selected_op;

	if (!(sam->instrs_asm = (t_instr_asm*)malloc(sizeof(t_instr_asm)
		* sam->nb_instrs)))
		return (0);
	i = 0;
	while (i < sam->nb_instrs)
	{
		selected_op = search_op(sam->instrs[i].command);
		sam->instrs_asm[i].op_code = g_op_tab[selected_op].opcode;
		sam->instrs_asm[i].ocp = get_ocp(sam->instrs[i].args,
		sam->instrs_asm[i].op_code);
		j = 0;
		while (j < sam->instrs[i].nb_arg)
		{
			size_arg(sam->instrs[i].args[j],
			&sam->instrs_asm[i].op_args[j], selected_op);
			j++;
		}
		i++;
	}
	return (1);
}

void	encode_instrs(t_asm *sam)
{
	int i;
	int j;

	i = 0;
	while (i < sam->nb_instrs)
	{
		j = 0;
		while (j < sam->instrs[i].nb_arg)
		{
			encode_arg(sam->instrs[i].args[j], &sam->instrs_asm[i].op_args[j]);
			j++;
		}
		i++;
	}
}

int		compile(t_asm *sam)
{
	if (!check_instrs(sam->instrs, sam->nb_instrs, sam->labels))
		return (0);
	if (!get_size_instrs(sam))
		return (FREE);
	sam->header.prog_size = handle_pos(sam);
	if (!get_labels_value(sam))
	{
		if (sam->instrs_asm)
			free(sam->instrs_asm);
		return (FREE);
	}
	encode_instrs(sam);
	if (!write_champ(sam))
	{
		ft_putendl_fd("Error", 2);
		return (0);
	}
	return (1);
}
