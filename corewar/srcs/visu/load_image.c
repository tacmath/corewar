/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   load_image.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 15:58:54 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 16:47:11 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static int	imgs_load(t_vm *vm, char *arr_img[4], SDL_Surface **surface)
{
	char		*tmp;
	int			i;

	i = 0;
	while (i < 4)
	{
		if (!(tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, IMAGE_PATH,
						arr_img[i])) || !(surface[i] = IMG_Load(tmp)))
			return (0);
		free(tmp);
		i++;
	}
	return (1);
}

static int	init_champ_jauge(t_vm *vm)
{
	char *arr_img[4];

	arr_img[0] = "JaugeChamp1_Opaque.png";
	arr_img[1] = "JaugeChamp2_Opaque.png";
	arr_img[2] = "JaugeChamp3_Opaque.png";
	arr_img[3] = "JaugeChamp4_Opaque.png";
	if (!imgs_load(vm, arr_img, vm->visu.champ_jauge_src))
		return (0);
	arr_img[0] = "JaugeChamp1_Halo.png";
	arr_img[1] = "JaugeChamp2_Halo.png";
	arr_img[2] = "JaugeChamp3_Halo.png";
	arr_img[3] = "JaugeChamp4_Halo.png";
	if (!imgs_load(vm, arr_img, vm->visu.champ_jauge_halo_src))
		return (0);
	SDL_SetSurfaceBlendMode(vm->visu.champ_jauge_halo_src[0],
			SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(vm->visu.champ_jauge_halo_src[1],
			SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(vm->visu.champ_jauge_halo_src[2],
			SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(vm->visu.champ_jauge_halo_src[3],
			SDL_BLENDMODE_NONE);
	return (1);
}

static int	init_champ(t_vm *vm)
{
	char *tmp;
	char *arr_img[4];

	if (!(tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, IMAGE_PATH,
					"Square0_Halo.png")) ||
			!(vm->visu.process_src = IMG_Load(tmp)))
		return (0);
	free(tmp);
	arr_img[0] = "Square1_Halo.png";
	arr_img[1] = "Square2_Halo.png";
	arr_img[2] = "Square3_Halo.png";
	arr_img[3] = "Square4_Halo.png";
	if (!imgs_load(vm, arr_img, vm->visu.champ_src))
		return (0);
	SDL_SetSurfaceBlendMode(vm->visu.process_src, SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(vm->visu.champ_src[0], SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(vm->visu.champ_src[1], SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(vm->visu.champ_src[2], SDL_BLENDMODE_NONE);
	SDL_SetSurfaceBlendMode(vm->visu.champ_src[3], SDL_BLENDMODE_NONE);
	return (1);
}

int			load_images(t_vm *vm)
{
	char *tmp;

	if (!(tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, IMAGE_PATH,
			"frame.png")))
		return (0);
	if (!(vm->visu.log_background = IMG_Load(tmp)))
		return (0);
	free(tmp);
	if (!(tmp = ft_strjoin_mult(4, vm->visu.path, ASSET_PATH, IMAGE_PATH,
			"Area.png")))
		return (0);
	if (!(vm->visu.arena_background = IMG_Load(tmp)))
		return (0);
	free(tmp);
	if (!init_champ(vm) || !init_cycle(vm) || !init_champ_jauge(vm))
		return (0);
	return (1);
}
