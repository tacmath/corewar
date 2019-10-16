/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 14:37:19 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/29 14:16:50 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "asm.h"

int		get_flags_and_file(t_asm *parse, int ac, char **av)
{
	int n;

	n = 0;
	while (++n < ac)
		if (!parse->file_name)
		{
			if (av[n][ft_strlen(av[n]) - 1] == 's'
				&& av[n][ft_strlen(av[n]) - 2] == '.')
			{
				if (!(parse->file_name = ft_strdup(av[n])))
					return (!ft_printf("Usage: ./asm <sourcefile.s>\n"));
			}
			else
				return (!ft_printf("%s is not a .s file\n", av[n]));
		}
		else
			return (!ft_printf("Usage: ./asm <sourcefile.s>\n"));
	if (!parse->file_name)
		return (!ft_printf("Usage: ./asm <sourcefile.s>\n"));
	return (1);
}

void	print_info(t_asm *parse)
{
	int n;

	ft_printf("name %s\ncomment%s\n",
		parse->header.prog_name, parse->header.how);
	ft_printf("nb command %d\n", parse->nb_instrs);
	n = -1;
	while (parse->labels[++n].label)
		ft_printf("%-15s%d\n",
		parse->labels[n].label, parse->labels[n].pos);
	n = -1;
	while (parse->instrs[++n].command)
		ft_printf("%-15s%-15s%-15s%s\n", parse->instrs[n].command,
		parse->instrs[n].args[0], parse->instrs[n].args[1],
		parse->instrs[n].args[2]);
}

int		main(int ac, char **av)
{
	t_asm	*parse;
	int		fd;
	int		error;

	parse = 0;
	if (!(parse = ft_memalloc(sizeof(t_asm)))
			|| !(parse->labels = ft_memalloc(sizeof(t_label)))
			|| !(parse->instrs = ft_memalloc(sizeof(t_instr)))
			|| !get_flags_and_file(parse, ac, av))
		return (free_asm(parse));
	if ((fd = open(parse->file_name, O_RDONLY)) == -1)
	{
		ft_printf("Can't read source file %s\n", parse->file_name);
		return (free_asm(parse));
	}
	if (!get_comment_and_name(parse, fd)
		|| !get_command_and_label(parse, fd))
	{
		get_next_line(fd, 0);
		close(fd);
		return (free_asm(parse));
	}
	if (close(fd) == -1 || !(error = compile(parse)))
		return (free_asm(parse));
	return (!free_asm(parse));
}
