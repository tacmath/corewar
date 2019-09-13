/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 15:21:17 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 13:44:49 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		remove_comment(char *line)
{
	char	*tmp;

	tmp = ft_strchr(line, COMMENT_CHAR);
	if (tmp)
		tmp[0] = 0;
	tmp = ft_strchr(line, ';');
	if (tmp)
		tmp[0] = 0;
	return (1);
}

char	*jump_space(char *line)
{
	int n;

	n = 0;
	while (line[n] == ' ' || line[n] == '\t')
		n++;
	return (&line[n]);
}

int		free_asm(t_asm *parse)
{
	int n;
	int m;

	if (!parse)
		return (-1);
	n = -1;
	while (parse->labels && parse->labels[++n].label)
		free(parse->labels[n].label);
	if (parse->labels)
		free(parse->labels);
	n = -1;
	while (parse->instrs && parse->instrs[++n].command)
	{
		free(parse->instrs[n].command);
		m = -1;
		while (++m < MAX_ARGS_NUMBER)
			free(parse->instrs[n].args[m]);
	}
	free(parse->file_name);
	free(parse->instrs);
	free(parse->instrs_asm);
	free(parse);
	return (-1);
}

int		ft_search_char(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	print_instrs(t_asm sam)
{
	int i;
	int j;

	i = 0;
	while (i < sam.nb_instrs)
	{
		ft_printf("command: %s\n", sam.instrs[i].command);
		ft_printf("opcode: %d\n", sam.instrs_asm[i].op_code);
		ft_printf("ocp: %X\n", sam.instrs_asm[i].ocp);
		j = 0;
		while (j < sam.instrs[i].nb_arg)
		{
			ft_printf("Arg num %d:\n", j + 1);
			ft_printf("\tnb_bytes: %d\n",
			sam.instrs_asm[i].op_args[j].nb_bytes);
			ft_printf("\tvalue: %s\n", sam.instrs[i].args[j]);
			ft_printf("\tvalue encoded: %X\n",
			sam.instrs_asm[i].op_args[j].arg);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
