/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   music.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:56:31 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 18:05:47 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"
#include <dirent.h>

int		file_name_realloc(char ***file_name, char *new_name)
{
	int		n;
	int		len;
	char	**tmp;

	len = -1;
	while ((*file_name)[++len])
		;
	if (!(tmp = ft_memalloc(sizeof(char**) * (len + 2))))
		return (0);
	n = -1;
	while (++n < len)
		tmp[n] = (*file_name)[n];
	if (!(tmp[n] = ft_strdup(new_name)))
		return (0);
	free(*file_name);
	*file_name = tmp;
	return (1);
}

char	**get_files(char *path)
{
	DIR				*dir;
	struct dirent	*info;
	char			**file_name;

	if (!(dir = opendir(path)))
		return (0);
	if (!(file_name = ft_memalloc(sizeof(char*))))
		return (0);
	while ((info = readdir(dir)))
		if (info->d_name[0] != '.')
			if (!file_name_realloc(&file_name, info->d_name))
				return (0);
	closedir(dir);
	return (file_name);
}

char	*get_groove(char *path)
{
	int		n;
	char	**file_name;
	char	*file_path;

	if (!(file_name = get_files(path)))
		return (NULL);
	n = -1;
	while (file_name[++n])
		;
	if (!n)
	{
		ft_super_free(2, path, file_name);
		return (NULL);
	}
	n = rand() % n;
	if (!(file_path = ft_strjoin(path, file_name[n])))
		return (0);
	free(path);
	n = -1;
	while (file_name[++n])
		free(file_name[n]);
	free(file_name);
	return (file_path);
}

void	play_music(t_vm *vm)
{
	char *tmp;

	tmp = 0;
	if (vm->visu.mode == KITSH)
	{
		if (!(tmp = get_groove(ft_strjoin_mult(4, vm->visu.path,
							ASSET_PATH, SOUND_PATH, "kitch/"))))
			return ;
	}
	else if (!(tmp = get_groove(ft_strjoin_mult(4, vm->visu.path,
						ASSET_PATH, SOUND_PATH, "non_kitch/"))))
		return ;
	if (!(vm->visu.mus = Mix_LoadMUS(tmp)))
	{
		free(tmp);
		return ;
	}
	free(tmp);
	Mix_Volume(-1, MIX_MAX_VOLUME / 4);
}
