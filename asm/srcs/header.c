/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   header.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/21 15:20:46 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 15:34:09 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		get_name(int fd, char *line, char **name, t_asm *parse)
{
	if (!ft_strncmp(NAME_CMD_STRING, line, ft_strlen(NAME_CMD_STRING)))
	{
		if (*name)
			return (0);
		line = &line[ft_strlen(NAME_CMD_STRING)];
		line = jump_space(line);
		if (line[0] != '"')
			return (0);
		*name = get_str(fd, line, parse, 0);
		if (!(*name))
			return (0);
	}
	else
		return (0);
	return (1);
}

int		get_comment(int fd, char *line, char **comment, t_asm *parse)
{
	if (!ft_strncmp(COMMENT_CMD_STRING, line, ft_strlen(COMMENT_CMD_STRING)))
	{
		if (*comment)
			return (0);
		line = &line[ft_strlen(COMMENT_CMD_STRING)];
		line = jump_space(line);
		if (line[0] != '"')
			return (0);
		*comment = get_str(fd, line, parse, 0);
		if (!(*comment))
			return (0);
	}
	else
		return (0);
	return (1);
}

int		fill_header(t_asm *parse, char *name, char *comment)
{
	int tmp;

	tmp = COREWAR_EXEC_MAGIC;
	parse->header.magic = *(unsigned int*)mem_swap(&tmp, sizeof(tmp));
	ft_strncpy(parse->header.prog_name, name, PROG_NAME_LENGTH);
	free(name);
	ft_strncpy(parse->header.how, comment, COMMENT_LENGTH);
	free(comment);
	return (1);
}

int		get_comment_and_name(t_asm *parse, int fd)
{
	int		n;
	char	*line;
	char	*name;
	char	*comment;

	line = 0;
	name = 0;
	comment = 0;
	while ((n = -1))
	{
		if (get_next_line(fd, &line) < 1 && ft_dprintf(2, "file empty\n"))
			return (ft_super_free(2, name, comment));
		parse->line++;
		remove_comment(line);
		while (line[++n] == ' ' || line[n] == '\t')
			;
		if (line[n] && !get_comment(fd, &line[n], &comment, parse)
				&& !get_name(fd, &line[n], &name, parse))
			return (ft_printf("Invalid name or comment\n")
					&& ft_super_free(3, line, name, comment));
			free(line);
		if (name && comment)
			return (fill_header(parse, name, comment));
	}
	return (1);
}
