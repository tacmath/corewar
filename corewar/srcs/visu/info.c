/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   info.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:56:04 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 15:10:52 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

SDL_Rect	treat_coord(t_vm *vm, int x, int y, int nb_info)
{
	SDL_Rect	coord;
	SDL_Rect	other_coord;

	coord.w = vm->visu.memory_coord.w / 6;
	coord.h = (vm->visu.command_text[0]->h + 1) * nb_info;
	coord.h += coord.h / 10;
	if (x < vm->visu.memory_coord.x)
		x = vm->visu.memory_coord.x;
	if (x > vm->visu.memory_coord.w + vm->visu.memory_coord.x - coord.w)
		x = vm->visu.memory_coord.w + vm->visu.memory_coord.x - coord.w;
	if (y + vm->visu.mem_len.h + coord.h + 1 + vm->visu.memory_coord.y <=
		vm->visu.memory_coord.h)
		y += vm->visu.mem_len.h + 1;
	else
		y -= (coord.h + 1);
	coord.x = x;
	coord.y = y;
	SDL_FillRect(vm->visu.window_surface, &coord, 0x00B8f1);
	other_coord = coord;
	other_coord.x += 2;
	other_coord.y += 2;
	other_coord.w -= 4;
	other_coord.h -= 4;
	SDL_FillRect(vm->visu.window_surface, &other_coord, 0);
	return (coord);
}
