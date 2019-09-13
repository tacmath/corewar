/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   info_instr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:35:02 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:36:40 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static char	*ft_ocptoa(char ocp, char nb_args)
{
	char	tmp;
	int		i;
	int		j;
	char	*ret;

	if (!(ret = ft_strnew(4 * nb_args - 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < nb_args)
	{
		tmp = (ocp >> (2 * (3 - i))) & 3;
		if (tmp == REG_CODE)
			ft_strcpy(&(ret[j]), "REG");
		else if (tmp == DIR_CODE)
			ft_strcpy(&(ret[j]), "DIR");
		else if (tmp == IND_CODE)
			ft_strcpy(&(ret[j]), "IND");
		j += 3;
		if (i != nb_args - 1)
			ret[j++] = '-';
	}
	return (ret);
}

static int	trasform_info(char **info, t_instr_v instr, char *tmp)
{
	if (!(info[0] = ft_strdup("instruction")) ||
			!(info[1] = ft_strdup(g_op_tab[(int)instr.instr - 1].name)))
		return (0);
	tmp = instr.ocp != 255 ? ft_ocptoa(instr.ocp, instr.nb_args) :
		ft_strdup("none");
	if (!(info[2] = tmp))
		return (0);
	tmp = ft_uitoa_base(instr.args[0], 16);
	if (!(info[3] = ft_strjoin("0x", tmp)))
		return (0);
	free(tmp);
	if (instr.nb_args == 1)
		return (1);
	tmp = ft_uitoa_base(instr.args[1], 16);
	if (!(info[4] = ft_strjoin("0x", tmp)))
		return (0);
	free(tmp);
	if (instr.nb_args == 2)
		return (1);
	tmp = ft_uitoa_base(instr.args[2], 16);
	if (!(info[5] = ft_strjoin("0x", tmp)))
		return (0);
	free(tmp);
	return (1);
}

static int	print_info_mem2(char ***info, SDL_Rect *coord, t_instr_v instr)
{
	char *tmp;

	tmp = NULL;
	if (!(*info = ft_memalloc(sizeof(char*) * (7))) ||
			!trasform_info(*info, instr, tmp))
	{
		free_info(*info);
		return (0);
	}
	coord->x += coord->w / 20;
	coord->y += coord->h / 20;
	return (1);
}

int			print_info_mem(t_vm *vm, SDL_Rect coord, t_instr_v instr)
{
	SDL_Rect	info_coord;
	SDL_Surface	*text;
	char		**info;
	int			n;

	if (!print_info_mem2(&info, &coord, instr))
		return (0);
	n = -1;
	while (info[++n])
	{
		info_coord = coord;
		SDL_BlitSurface(vm->visu.command_text[n], 0,
				vm->visu.window_surface, &info_coord);
		info_coord = coord;
		info_coord.x += coord.w / 3;
		if (!(text = TTF_RenderText_Blended(vm->visu.info_font, info[n],
						vm->visu.text_color)))
			return (0);
		SDL_BlitSurface(text, 0, vm->visu.window_surface, &info_coord);
		SDL_FreeSurface(text);
		coord.y += text->h + 1;
	}
	free_info(info);
	return (1);
}
