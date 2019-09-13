/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:58:14 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 17:17:23 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int					ft_sqrt(int nb)
{
	int i;

	i = 0;
	while (i * i < nb)
		i++;
	return (i);
}

unsigned char		color_max(unsigned char c1, unsigned char c2)
{
	if (c1 > c2)
		return (c1);
	else
		return (c2);
}

void				free_info(char **info)
{
	int n;

	n = -1;
	while (info[++n])
		free(info[n]);
	free(info);
}

void				quit_visu(t_vm *vm)
{
	free(vm->visu.path);
	free_all_old_images(vm);
	free_images_src(vm);
	SDL_DestroyWindow(vm->visu.window);
	Mix_FreeMusic(vm->visu.mus);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	clean(vm);
	exit(0);
}

char				*get_champ_name(t_vm *vm, int id, int max_len)
{
	int		len;
	char	*name;

	len = -1;
	while (vm->champs_decoded[id - 1].header.prog_name[++len])
		if (ft_isprint(vm->champs_decoded[id - 1].header.prog_name[len]))
			break ;
	if (!vm->champs_decoded[id - 1].header.prog_name[len])
		return (ft_strdup("NO NAME"));
	len = ft_strlen(vm->champs_decoded[id - 1].header.prog_name);
	if (len > max_len)
	{
		if (!(name = ft_memalloc(sizeof(char) * (max_len + 4))))
			return (0);
		ft_strncpy(name, vm->champs_decoded[id - 1].header.prog_name, max_len);
		name[max_len] = '.';
		name[max_len + 1] = '.';
		name[max_len + 2] = '.';
	}
	else if (!(name = ft_strdup(vm->champs_decoded[id - 1].header.prog_name)))
		return (0);
	return (name);
}
