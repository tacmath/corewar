/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   command.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 15:20:10 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/29 15:13:38 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int	get_one_arg(t_instr *tmp, char **line)
{
	int		n;
	int		ret;
	char	*tmp_line;

	tmp_line = *line;
	*line = jump_space(*line);
	if (!(*line)[0])
	{
		*line = tmp_line;
		return (1);
	}
	ret = 0;
	n = -1;
	while ((*line)[++n] && (*line)[n] != SEPARATOR_CHAR)
		if ((*line)[n] != ' ' && (*line)[n] != '\t' && (*line)[n])
			ret = n + 1;
	if (!(tmp->args[(int)tmp->nb_arg] = ft_memalloc(sizeof(char) * (ret + 1))))
		return (0);
	ft_strncpy(tmp->args[(int)tmp->nb_arg++], *line, ret);
	if ((*line)[n])
		n++;
	*line = &(*line)[n];
	return (1);
}

int	command_realloc(t_asm *parse, t_instr new)
{
	int		n;
	int		len;
	t_instr	*tmp;

	len = -1;
	while (parse->instrs[++len].command)
		;
	if (!(tmp = ft_memalloc(sizeof(t_instr) * (len + 2))))
		return (0);
	n = -1;
	while (++n < len)
		tmp[n] = parse->instrs[n];
	tmp[n] = new;
	free(parse->instrs);
	parse->instrs = tmp;
	parse->nb_instrs++;
	return (1);
}

int	get_all_args(t_asm *parse, char *line, t_instr tmp)
{
	int n;

	n = -1;
	while (++n < MAX_ARGS_NUMBER)
		if (!get_one_arg(&tmp, &line))
		{
			return (ft_super_free(4, tmp.command, tmp.args[0],
					tmp.args[1], tmp.args[2]));
		}
	if (line[-1] == SEPARATOR_CHAR && (line = jump_space(line)) && !line[0])
	{
		ft_super_free(4, tmp.command, tmp.args[0], tmp.args[1], tmp.args[2]);
		return (!ft_dprintf(2, "Syntax error line %d\n", tmp.line));
	}
	if ((line = jump_space(line)) && line[0])
	{
		ft_super_free(4, tmp.command, tmp.args[0], tmp.args[1], tmp.args[2]);
		return (!ft_dprintf(2,
		"Error line %d : too many arguments\n", tmp.line));
	}
	if (!command_realloc(parse, tmp))
		return (ft_super_free(4, tmp.command,
					tmp.args[0], tmp.args[1], tmp.args[2]));
		return (1);
}

int	get_command(t_asm *parse, char *line)
{
	int		n;
	t_instr	tmp;

	line = jump_space(line);
	if (line[0] == SEPARATOR_CHAR)
	{
		return (!ft_dprintf(2,
		"The command line %d begins with a f*cking coma biatch 🤦‍♀️ 🤦\n",
		parse->line));
	}
	if (!line[0])
		return (1);
	n = -1;
	while (line[++n] && ft_strchr(LABEL_CHARS, line[n]))
		;
	ft_bzero(&tmp, sizeof(t_instr));
	tmp.line = parse->line;
	if (!(tmp.command = ft_memalloc(sizeof(char) * (n + 2))))
		return (0);
	ft_strncpy(tmp.command, line, n);
	line = &line[n];
	if (!get_all_args(parse, line, tmp))
		return (0);
	return (1);
}
