/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/06 18:46:39 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/10 16:38:08 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int	basic_option(char *str, t_options *options)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'v')
			options->verbose = 1;
		else if (str[i] == 'g')
			options->visu = 1;
		else
			return (0);
		i++;
	}
	return (1);
}

int	option_n(char **av, int *i, int *nb_champs, t_options *options)
{
	uint32_t	num;
	int			j;

	num = (uint32_t)ft_atoi(av[*i + 1]);
	if (num == 0)
		return (0);
	j = -1;
	while (++j < *nb_champs)
		if (num == options->num_champs[j])
		{
			num = next_num(options->num_champs, *nb_champs);
			break ;
		}
	options->num_champs[*nb_champs] = num;
	options->players_file[*nb_champs] = av[*i + 2];
	(*nb_champs)++;
	*i += 2;
	return (1);
}

int	getelse(int *nb_champs, t_options *options, char **av, int i)
{
	if (*nb_champs >= MAX_PLAYERS)
		return (0);
	options->num_champs[*nb_champs] = next_num(options->num_champs, *nb_champs);
	options->players_file[*nb_champs] = av[i];
	(*nb_champs)++;
	return (1);
}

int	getmoreelse(char **av, int *i, int ac, t_options *options)
{
	if (!ft_strcmp(av[*i], "-d"))
	{
		if (*i + 1 >= ac || !is_int(av[*i + 1]))
			return (0);
		options->cycle_dump = ft_atoi(av[*i + 1]);
		(*i)++;
	}
	else if (!basic_option(av[*i] + 1, options))
		return (0);
	return (1);
}

int	get_options(int ac, char **av, t_options *options)
{
	int	i;
	int nb_champs;

	i = -1;
	nb_champs = 0;
	while (++i < ac)
	{
		if (av[i][0] == '-')
		{
			if (!ft_strcmp(av[i], "-n"))
			{
				if (i + 2 >= ac || av[i + 2][0] == '-' || !is_uint(av[i + 1]) ||
						!option_n(av, &i, &nb_champs, options))
					return (0);
			}
			else if (!getmoreelse(av, &i, ac, options))
				return (0);
		}
		else if (!getelse(&nb_champs, options, av, i))
			return (0);
	}
	options->nb_champs = nb_champs;
	return (1);
}
