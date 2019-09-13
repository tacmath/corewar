/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_cycle.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 16:04:36 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 16:51:37 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	init_cycle2(t_vm *vm, unsigned char *color, int n)
{
	color[2] = color_max(((CYCLE2 & 0xFF0000) >> 16) * n /
			(vm->visu.memory_coord.w / 2), (CYCLE1 & 0xFF0000) >> 16);
	color[1] = color_max(((CYCLE2 & 0xFF00) >> 8) * n /
			(vm->visu.memory_coord.w / 2), (CYCLE1 & 0xFF00) >> 8);
	color[0] = color_max((CYCLE2 & 0xFF) * n /
			(vm->visu.memory_coord.w / 2), CYCLE1 & 0xFF);
}

static void	init_cycle3(t_vm *vm, unsigned char *color, int n)
{
	int tmp;

	tmp = (vm->visu.memory_coord.w / 2) - (n - (vm->visu.memory_coord.w / 2));
	color[2] = color_max(((CYCLE1 & 0xFF0000) >> 16) * tmp /
			(vm->visu.memory_coord.w / 2), (CYCLE2 & 0xFF0000) >> 16);
	color[1] = color_max(((CYCLE1 & 0xFF00) >> 8) * tmp /
			(vm->visu.memory_coord.w / 2), (CYCLE2 & 0xFF00) >> 8);
	color[0] = color_max((CYCLE1 & 0xFF) * tmp /
			(vm->visu.memory_coord.w / 2), CYCLE2 & 0xFF);
}

int			init_cycle(t_vm *vm)
{
	SDL_Rect		rect;
	unsigned char	color[4];
	int				n;

	if (!(vm->visu.cycle =
	SDL_CreateRGBSurface(0, vm->visu.memory_coord.w, 7, 32, 0, 0, 0, 0)))
		return (0);
	rect.y = 0;
	rect.w = 1;
	rect.h = 7;
	color[3] = 0;
	n = -1;
	while (++n < vm->visu.memory_coord.w)
	{
		rect.x = n;
		if (vm->visu.memory_coord.w / 2 > n)
			init_cycle2(vm, color, n);
		else
			init_cycle3(vm, color, n);
		SDL_FillRect(vm->visu.cycle, &rect, *(int*)color);
	}
	return (1);
}
