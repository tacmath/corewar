/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   info_process.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:36:49 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:37:45 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	treat_info_process(t_vm *vm, char **info, t_process process)
{
	char	*tmp;
	int		n;

	if (!(info[0] = ft_strdup("process"))
			|| !(info[1] = ft_itoa(process.num))
			|| !(info[2] = get_champ_name(vm, process.champ_id, 10))
			|| !(info[3] = ft_itoa(process.carry))
			|| !(info[6] = ft_itoa(process.cycles_left)))
		return (0);
	if (!(tmp = ft_strdup(process.live ? "yup" : "nop")))
		return (0);
	info[4] = tmp;
	if (process.op == -1)
	{
		if (!(tmp = ft_strdup("none")))
			return (0);
		info[5] = tmp;
	}
	else if (!(info[5] = ft_strdup(g_op_tab[(int)process.op - 1].name)))
		return (0);
	n = 7;
	while (++n < 24)
		if (!(info[n] = ft_uitoa_base(process.regs[n - 8], 16)))
			return (0);
	return (1);
}

static int	free_info_process(char ***info)
{
	int n;

	if (!(*info) || !info)
		return (1);
	n = -1;
	while (++n < 24)
		free((*info)[n]);
	free(*info);
	*info = 0;
	return (1);
}

static void	print_info_process2(SDL_Rect *info_coord,
		SDL_Rect coord, int n, t_vm *vm)
{
	*info_coord = coord;
	SDL_BlitSurface(vm->visu.process_text[vm->visu.info_pages - 1][n],
			0, vm->visu.window_surface, info_coord);
	*info_coord = coord;
	info_coord->x += coord.w / 3;
}

int			print_info_process(t_vm *vm, SDL_Rect coord,
		t_process process, int change)
{
	SDL_Rect		info_coord;
	SDL_Surface		*text;
	static char		**info = 0;
	int				n;

	if (change == 2 && free_info_process(&info))
		return (1);
	if (change && free_info_process(&info) && (!(info =
ft_memalloc(sizeof(char*) * (25))) || !treat_info_process(vm, info, process)))
		return (0);
	coord.x += coord.w / 20;
	coord.y += coord.h / 20;
	n = -1;
	while (info[++n + (8 * (vm->visu.info_pages - 1))] && n < 8)
	{
		print_info_process2(&info_coord, coord, n, vm);
		if (!(text = TTF_RenderText_Blended(vm->visu.info_font,
			info[n + (8 * (vm->visu.info_pages - 1))], vm->visu.text_color)))
			return (0);
		SDL_BlitSurface(text, 0, vm->visu.window_surface, &info_coord);
		SDL_FreeSurface(text);
		coord.y += text->h + 1;
	}
	return (1);
}
