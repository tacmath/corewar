/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   options.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/06 18:46:39 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/07 16:35:37 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int			is_uint(char *str)
{
	int i;
	int len;

	i = -1;
	while (str[++i])
		if (i >= 10 || str[i] > '9' || str[i] < '0')
			return (0);
	len = i;
	return (!(len == 10 && ft_strcmp(str, "4294967295") > 0));
}

int			is_int(char *str)
{
	int i;
	int len;

	i = -1;
	while (str[++i])
		if (i >= 10 || str[i] > '9' || str[i] < '0')
			return (0);
	len = i;
	return (!(len == 10 && ft_strcmp(str, "2147483647") > 0));
}

uint32_t	next_num(uint32_t *arr, int nb_champs)
{
	int			i;
	uint32_t	j;
	int			test;

	test = 1;
	j = 0;
	while (test)
	{
		j++;
		test = 0;
		i = -1;
		while (++i < nb_champs)
			if (arr[i] == j)
			{
				test = 1;
				break ;
			}
	}
	return (j);
}

void		print_options(t_options *options)
{
	int i;

	ft_printf("Nombre de joueurs: %d\n", options->nb_champs);
	i = -1;
	ft_printf("Les fichiers:\n");
	while (++i < options->nb_champs)
		ft_printf("Fichier %d: %s\n", i + 1, options->players_file[i]);
	ft_printf("Numéro des joueurs:\n");
	i = -1;
	while (++i < options->nb_champs)
		ft_printf("Joueur %d, numéro %u\n", i + 1, options->num_champs[i]);
	ft_printf("Verbose: %s\n", options->verbose ? "Activé" : "Désactivé");
	ft_printf("Visu: %s\n", options->visu ? "Activé" : "Désactivé");
	if (options->cycle_dump == -1)
		ft_printf("Pas de dump\n");
	else
		ft_printf("Dump au cycle %d\n", options->cycle_dump);
}
