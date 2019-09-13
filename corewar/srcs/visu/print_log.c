/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   fill_surface.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:55:53 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/13 12:38:32 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	fill_info(t_vm *vm, char **info)
{
	char *tmp;

	if (!(info[0] = ft_itoa(vm->cycle)) ||
			!(info[1] = ft_itoa(vm->nb_procs)) ||
			!(info[2] = ft_itoa(vm->cycle_to_die)))
		return (0);
	if (vm->visu.speed > 0)
		tmp = ft_itoa(vm->visu.speed);
	else
		tmp = ft_dtoa(1 / (double)(vm->visu.speed * -1), 4);
	if (!(info[3] = ft_strjoin("x ", tmp)))
		return (0);
	free(tmp);
	return (1);
}

int			print_info_log_text(t_vm *vm, char *info, int n)
{
	SDL_Rect	coord;
	SDL_Surface	*text;

	coord.y = vm->visu.log_coord.y + ((vm->visu.log_coord.h * 15) / 20) + n *
	(6 * vm->visu.little_info->h) / 5 + vm->visu.little_info->h / 2
	- vm->visu.info_text[n]->h / 2;
	coord.x = vm->visu.log_coord.x + vm->visu.log_coord.w / 2 -
	vm->visu.log_coord.w / 50 - vm->visu.info_text[n]->w;
	SDL_BlitSurface(vm->visu.info_text[n], 0, vm->visu.window_surface, &coord);
	if (!(text = TTF_RenderText_Blended(vm->visu.info_font,
			info, vm->visu.text_color)))
		return (0);
	coord.y = vm->visu.log_coord.y + ((vm->visu.log_coord.h * 15) / 20)
		+ n * (6 * vm->visu.little_info->h) / 5;
	coord.x = vm->visu.log_coord.x + vm->visu.log_coord.w / 2 +
	vm->visu.log_coord.w / 50;
	SDL_BlitSurface(vm->visu.little_info, 0, vm->visu.window_surface, &coord);
	coord.x += vm->visu.little_info->w / 2 - text->w / 2;
	coord.y += vm->visu.little_info->h / 2 - text->h / 2;
	SDL_BlitSurface(text, 0, vm->visu.window_surface, &coord);
	SDL_FreeSurface(text);
	return (1);
}

static int	print_info_log(t_vm *vm)
{
	char	**info;
	int		n;

	if (!(info = ft_memalloc(sizeof(char*) * (5))) || !fill_info(vm, info))
		return (0);
	n = -1;
	while (info[++n])
		if (!print_info_log_text(vm, info[n], n))
			return (0);
	free_info(info);
	return (1);
}

void		print_log(t_vm *vm)
{
	SDL_BlitSurface(vm->visu.log, 0, vm->visu.window_surface, &vm->visu.log_coord);
	print_jauge(vm);
	print_info_log(vm);
}
