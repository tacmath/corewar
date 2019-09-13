/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   resize_image.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 16:04:16 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 16:36:20 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	resize_all_images2(t_vm *vm, SDL_Rect *rect, int w, int h)
{
	SDL_BlitScaled(vm->visu.process_src, 0, vm->visu.process, 0);
	SDL_BlitScaled(vm->visu.process_src, 0, vm->visu.highlight, 0);
	SDL_BlitScaled(vm->visu.champ_src[0], 0, vm->visu.champ[0], 0);
	SDL_BlitScaled(vm->visu.champ_src[1], 0, vm->visu.champ[1], 0);
	SDL_BlitScaled(vm->visu.champ_src[2], 0, vm->visu.champ[2], 0);
	SDL_BlitScaled(vm->visu.champ_src[3], 0, vm->visu.champ[3], 0);
	rect->w = vm->visu.mem_len.w * 0.8;
	rect->h = vm->visu.mem_len.h * 0.8;
	rect->x = w / 2 - rect->w / 2;
	rect->y = h / 2 - rect->h / 2;
	SDL_FillRect(vm->visu.process, rect,
			SDL_MapRGB(vm->visu.process->format, 0xFF, 0xFF, 0xFF));
	SDL_FillRect(vm->visu.champ[0], rect,
			SDL_MapRGB(vm->visu.champ[0]->format, 0xFF, 0x00, 0x3C));
	SDL_FillRect(vm->visu.champ[1], rect,
			SDL_MapRGB(vm->visu.champ[1]->format, 0xFF, 0xFF, 0x39));
	SDL_FillRect(vm->visu.champ[2], rect,
			SDL_MapRGB(vm->visu.champ[2]->format, 0x59, 0xFF, 0x63));
	SDL_FillRect(vm->visu.champ[3], rect,
			SDL_MapRGB(vm->visu.champ[3]->format, 0x6b, 0x68, 0xFF));
	rect->w = vm->visu.mem_len.w;
	rect->x = w / 2 - rect->w / 2;
	SDL_FillRect(vm->visu.highlight, rect,
			SDL_MapRGB(vm->visu.process->format, 0xFF, 0xFF, 0xFF));
}

static int	resize_all_images_if(t_vm *vm, int w, int h)
{
	return (
	!(vm->visu.process = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.process_src->format->format)) ||
	!(vm->visu.highlight = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.process_src->format->format)) ||
	!(vm->visu.champ[0] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_src[0]->format->format)) ||
	!(vm->visu.champ[1] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_src[1]->format->format)) ||
	!(vm->visu.champ[2] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_src[2]->format->format)) ||
	!(vm->visu.champ[3] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_src[3]->format->format)));
}

static int	resize_all_images_if2(t_vm *vm, int w, int h)
{
	return (
			!(vm->visu.champ_jauge[0] = SDL_CreateRGBSurface(
					0, w, h, 32, 0, 0, 0, 0)) ||
			!(vm->visu.champ_jauge[1] = SDL_CreateRGBSurface(
					0, w, h, 32, 0, 0, 0, 0)) ||
			!(vm->visu.champ_jauge[2] = SDL_CreateRGBSurface(
					0, w, h, 32, 0, 0, 0, 0)) ||
			!(vm->visu.champ_jauge[3] = SDL_CreateRGBSurface(
					0, w, h, 32, 0, 0, 0, 0)));
}

static int	resize_all_images_if3(t_vm *vm, int w, int h)
{
	return (
	!(vm->visu.champ_jauge_halo[0] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_jauge_halo_src[0]->format->format)) ||
	!(vm->visu.champ_jauge_halo[1] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_jauge_halo_src[1]->format->format)) ||
	!(vm->visu.champ_jauge_halo[2] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_jauge_halo_src[2]->format->format)) ||
	!(vm->visu.champ_jauge_halo[3] = SDL_CreateRGBSurfaceWithFormat(
			0, w, h, 32, vm->visu.champ_jauge_halo_src[3]->format->format)));
}

int			resize_all_images(t_vm *vm)
{
	int			i;
	int			w;
	int			h;
	SDL_Rect	rect;

	w = (vm->visu.mem_len.w * 0.8) * 1.9;
	h = (vm->visu.mem_len.h * 0.8) * 1.9;
	if (resize_all_images_if(vm, w, h))
		return (0);
	resize_all_images2(vm, &rect, w, h);
	get_width(vm, &w, &h, 0);
	if (resize_all_images_if2(vm, w, h))
		return (0);
	i = -1;
	while (++i < 4)
		SDL_BlitScaled(vm->visu.champ_jauge_src[i], 0,
				vm->visu.champ_jauge[i], 0);
	get_width(vm, &w, &h, 1);
	if (resize_all_images_if3(vm, w, h))
		return (0);
	i = -1;
	while (++i < 4)
		SDL_BlitScaled(vm->visu.champ_jauge_halo_src[i], 0,
				vm->visu.champ_jauge_halo[i], 0);
	return (1);
}
