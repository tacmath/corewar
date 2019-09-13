/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   label.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 15:19:40 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/21 15:59:24 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int	label_realloc(t_asm *parse, char *new)
{
	int		n;
	int		len;
	t_label	*tmp;

	len = -1;
	while (parse->labels[++len].label)
	{
		if (!ft_strcmp(parse->labels[len].label, new))
			return (!ft_printf(
	"Error line %d : the label %s is already defined\n", parse->line, new));
	}
	if (!(tmp = ft_memalloc(sizeof(t_label) * (len + 2))))
		return (0);
	n = -1;
	while (++n < len)
		tmp[n] = parse->labels[n];
	if (!(tmp[n].label = ft_strdup(new)))
		return (ft_super_free(1, tmp));
	tmp[n].pos = parse->nb_instrs;
	tmp[n].line = parse->line;
	free(parse->labels);
	parse->labels = tmp;
	return (1);
}

int	get_label(t_asm *parse, char **line)
{
	int n;

	*line = jump_space(*line);
	n = -1;
	while ((*line)[++n] && ft_strchr(LABEL_CHARS, (*line)[n]))
		;
	if ((*line)[n] != LABEL_CHAR)
		return (1);
	(*line)[n] = 0;
	if (!label_realloc(parse, *line))
		return (0);
	*line = &(*line)[n + 1];
	return (1);
}

int	get_command_and_label(t_asm *parse, int fd)
{
	char	*line;
	char	*mem;

	while (get_next_line(fd, &line) == 1)
	{
		parse->line++;
		remove_comment(line);
		mem = line;
		if (!get_label(parse, &line))
			return (ft_super_free(1, mem));
		if (!get_command(parse, line))
			return (ft_super_free(1, mem));
		free(mem);
	}
	return (1);
}

int	get_pos_label(char *label, t_label *labels)
{
	int i;

	i = 0;
	while (labels[i].label)
	{
		if (!ft_strcmp(label, labels[i].label))
			return (labels[i].pos_oct);
		i++;
	}
	return (-1);
}

int	get_labels_value(t_asm *sam)
{
	int		i;
	int		j;
	int		ix;
	char	*new_arg;

	i = -1;
	while (++i < sam->nb_instrs)
	{
		j = -1;
		while (++j < sam->instrs[i].nb_arg)
		{
			if ((ix = ft_search_char(sam->instrs[i].args[j], LABEL_CHAR)) != -1)
			{
				new_arg = strndup(sam->instrs[i].args[j], ix);
				new_arg = ft_strjoin_free(new_arg,
				ft_itoa(get_pos_label(sam->instrs[i].args[j] + ix + 1,
				sam->labels) - sam->instrs[i].pos));
				if (!new_arg)
					return (0);
				free(sam->instrs[i].args[j]);
				sam->instrs[i].args[j] = new_arg;
			}
		}
	}
	return (1);
}
