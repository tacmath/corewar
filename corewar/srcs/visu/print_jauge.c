/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_jauge.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:40:00 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:48:43 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	print_side_rail(t_vm *vm, SDL_Rect coord)
{
	SDL_Rect rail;

	rail.x = coord.x - 1 - vm->visu.champ_jauge[0]->w / 2;
	rail.h = vm->visu.champ_jauge[0]->h;
	rail.y = coord.y - rail.h;
	rail.w = 1;
	SDL_FillRect(vm->visu.window_surface, &rail, 0x00B8F1);
	rail.x += vm->visu.champ_jauge[0]->w + 1;
	SDL_FillRect(vm->visu.window_surface, &rail, 0x00B8F1);
}

static void	print_jauge_halo(t_vm *vm, SDL_Rect coord, SDL_Surface *halo,
		int len)
{
	SDL_Rect printed;
	SDL_Rect printed_coord;

	if (!len)
		return ;
	printed_coord = coord;
	printed.x = 0;
	printed.y = halo->h - halo->h / 20;
	printed.w = halo->w;
	printed.h = halo->h / 20;
	printed_coord.x -= printed.w / 2;
	SDL_BlitSurface(halo, &printed, vm->visu.window_surface, &printed_coord);
	printed_coord.y -= len;
	printed_coord.w = halo->w;
	printed_coord.h = len;
	printed.y -= halo->h - halo->h / 10;
	printed.h = halo->h - halo->h / 10;
	SDL_BlitScaled(halo, &printed, vm->visu.window_surface, &printed_coord);
	printed.x = 0;
	printed.y = 0;
	printed.w = halo->w;
	printed.h = halo->h / 20;
	printed_coord.y -= halo->h / 20;
	SDL_BlitSurface(halo, &printed, vm->visu.window_surface, &printed_coord);
}

static int	get_jauge_height(t_vm *vm, int max_len, int champ)
{
	int max;
	int n;

	max = 0;
	n = -1;
	while (++n < 4)
		max += vm->live_champs[n];
	if (max && vm->live_champs[champ])
		return ((max_len * vm->live_champs[champ]) / max);
	return (1);
}

static void	print_jauge2(SDL_Rect *coord, int x, int n, t_vm *vm)
{
	coord->x = vm->visu.log_coord.x + x * n + (vm->visu.log_coord.w / 10);
	coord->y = vm->visu.log_coord.y + ((vm->visu.log_coord.h * 13) / 20);
	print_side_rail(vm, *coord);
	coord->x = vm->visu.log_coord.x + x * n + (vm->visu.log_coord.w / 10) -
		(vm->visu.champ_jauge[0]->w + 2) / 2 - 1 -
		vm->visu.champ_name[n - 1]->w;
	coord->y = vm->visu.log_coord.y + ((vm->visu.log_coord.h * 13) / 20)
		- vm->visu.champ_name[n - 1]->h;
	SDL_BlitSurface(vm->visu.champ_name[n - 1], 0, vm->visu.window_surface,
			coord);
	coord->w = vm->visu.champ_jauge[0]->w;
	coord->h = get_jauge_height(vm, vm->visu.champ_jauge[n - 1]->h, n - 1);
	coord->x = vm->visu.log_coord.x + x * n + (vm->visu.log_coord.w / 10)
		- coord->w / 2;
	coord->y = vm->visu.log_coord.y + ((vm->visu.log_coord.h * 13) / 20)
		- coord->h;
	SDL_BlitScaled(vm->visu.champ_jauge[n - 1], 0, vm->visu.window_surface,
			coord);
	coord->x = vm->visu.log_coord.x + x * n + (vm->visu.log_coord.w / 10);
	coord->y = vm->visu.log_coord.y + ((vm->visu.log_coord.h * 13) / 20);
	print_jauge_halo(vm, *coord, vm->visu.champ_jauge_halo[n - 1], coord->h);
}

void		print_jauge(t_vm *vm)
{
	SDL_Rect	coord;
	int			x;
	int			n;

	x = ((vm->visu.log_coord.w * 8) / 10) / (vm->nb_champs + 1);
	n = 0;
	while (++n <= vm->nb_champs)
		print_jauge2(&coord, x, n, vm);
}
