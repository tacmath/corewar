/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: krambono <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/18 14:37:19 by krambono     #+#   ##    ##    #+#       */
/*   Updated: 2019/09/07 17:39:22 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int				get_champ2(t_champ_decoded *champ, int fd)
{
	int ret;

	if (!(champ->prog = ft_memalloc(champ->header.prog_size + 1)))
		return ((ALLOC_FAILED));
	if ((ret = read(fd, champ->prog, champ->header.prog_size + 1)) == -1)
		return ((READ_FAILED));
	if (ret != (int)champ->header.prog_size)
		return ((INVALID_HEADER));
	return (NO_ERROR);
}

int				get_champ(char *filename, t_champ_decoded *champ,
				int id, int visu_id)
{
	int	fd;
	int	ret;

	ft_bzero(champ, sizeof(t_champ_decoded));
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (error_int(OPEN_FAILED));
	if ((ret = read(fd, &champ->header, sizeof(t_header))) == -1)
		return (error_int(READ_FAILED));
	mem_swap(&champ->header.prog_size, 4);
	mem_swap(&champ->header.magic, 4);
	if (champ->header.magic != COREWAR_EXEC_MAGIC)
		return (error_int(INVALID_MAGIC));
	if (ret < (int)sizeof(t_header))
		return (error_int(SMALL_FILE));
	if (champ->header.prog_size > CHAMP_MAX_SIZE)
		return (error_int(BIG_FILE));
	if (champ->header.prog_name[PROG_NAME_LENGTH] ||
			champ->header.how[COMMENT_LENGTH])
		return (error_int(INVALID_HEADER));
	if ((ret = get_champ2(champ, fd)) != NO_ERROR)
		return (error_int(ret));
	champ->id = id;
	champ->visu_id = visu_id;
	return (1);
}

int				get_nb_champs(int ac, char **av)
{
	int n;
	int ret;

	n = 0;
	ret = 0;
	while (++n < ac)
		if (av[n][0] != '-' && ft_strcmp(av[n - 1], "-d") &&
				ft_strcmp(av[n - 1], "-dump"))
			ret++;
	return (ret);
}

void			*free_champs_decoded(t_champ_decoded *champs_decoded)
{
	int n;

	n = -1;
	while (champs_decoded[++n].prog)
		free(champs_decoded[n].prog);
	free(champs_decoded);
	return (NULL);
}

t_champ_decoded	*parser(char **players, int nb_champs, uint32_t *num_champs)
{
	t_champ_decoded		*champs_decoded;
	int					n;

	n = -1;
	champs_decoded = NULL;
	if (!(champs_decoded = ft_memalloc(sizeof(t_champ_decoded) *
					(nb_champs + 1))))
		return (error_null(BAD_FORMAT));
	while (++n < nb_champs)
	{
		if (!check_cor(players[n]))
		{
			free_champs_decoded(champs_decoded);
			return (error_null(BAD_FORMAT));
		}
		if (!get_champ(players[n], &champs_decoded[n], num_champs[n], n + 1))
			return (free_champs_decoded(champs_decoded));
	}
	return (champs_decoded);
}
