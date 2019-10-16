/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_str.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/06 18:28:25 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/16 13:43:35 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

char	*end_quote(char *ret, char *tmp, char *line)
{
	ret[0] = 0;
	ret = jump_space(&ret[1]);
	if (ret[0] != 0 && ret[0] != COMMENT_CHAR)
	{
		ft_super_free(2, tmp, line);
		return (0);
	}
	if (!(ret = ft_strjoin_mult(3, tmp, "\n", line)))
		return (0);
	ft_super_free(2, tmp, line);
	return (ret);
}

char	*mono_line(char *ret, char *line, int n)
{
	char	*tmp;

	ret[0] = 0;
	ret = jump_space(&ret[1]);
	if (ret[0] != 0 && ret[0] != COMMENT_CHAR)
		return (0);
	if (!(tmp = ft_strdup(&line[n])))
		return (0);
	return (tmp);
}

char	*get_str(int fd, char *line, t_asm *parse, int n)
{
	char	*tmp;
	char	*ret;

	if ((n = -1) && !line)
		return (0);
	while (line[++n] && line[n] != '"')
		;
	if ((ret = ft_strchr(&line[++n], '"')))
		return (mono_line(ret, line, n));
	else if (!(tmp = ft_strdup(&line[n])))
		return (0);
	while (1)
	{
		if (get_next_line(fd, &line) < 1 && !ft_super_free(1, tmp))
			return (NULL);
		parse->line++;
		if ((ret = ft_strchr(line, '"')))
			return (end_quote(ret, tmp, line));
		if (!(ret = ft_strjoin_mult(3, tmp, "\n", line)))
			return (0);
		ft_super_free(2, tmp, line);
		tmp = ret;
	}
	return (0);
}
