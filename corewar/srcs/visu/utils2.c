/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils2.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 16:05:40 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:27:06 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int			rev_image(SDL_Surface **new, SDL_Surface *ref)
{
	int	*pixels;
	int	*pixels_ref;
	int	x;
	int	y;

	if (!(*new = SDL_CreateRGBSurfaceWithFormat(0, ref->h, ref->w, 32,
					ref->format->format)))
		return (0);
	SDL_LockSurface(*new);
	pixels = (int*)(*new)->pixels;
	pixels_ref = (int*)ref->pixels;
	y = -1;
	while (++y < ref->h)
	{
		x = -1;
		while (++x < ref->w)
			pixels[ref->h * ((ref->w - 1) - x) + y] =
				pixels_ref[y * ref->w + x];
	}
	SDL_UnlockSurface(*new);
	SDL_FreeSurface(ref);
	return (1);
}

SDL_Surface	*create_empty_frame(t_len frame_len, int frame_color, int len)
{
	SDL_Surface *frame;
	SDL_Rect	coord;

	if (!(frame = SDL_CreateRGBSurface(0, frame_len.w, frame_len.h,
					32, 0, 0, 0, 0)))
		return (0);
	SDL_FillRect(frame, 0, 0);
	SDL_SetColorKey(frame, SDL_TRUE, 0);
	coord.x = 0;
	coord.y = 0;
	coord.w = frame_len.w;
	coord.h = len;
	SDL_FillRect(frame, &coord, frame_color);
	coord.y = frame_len.h - len;
	SDL_FillRect(frame, &coord, frame_color);
	coord.x = 0;
	coord.y = 0;
	coord.w = len;
	coord.h = frame_len.h;
	SDL_FillRect(frame, &coord, frame_color);
	coord.x = frame_len.w - len;
	SDL_FillRect(frame, &coord, frame_color);
	return (frame);
}

SDL_Surface	*create_filled_frame(t_len frame_len, int frame_color,
		int background_color, int len)
{
	SDL_Surface *frame;
	SDL_Rect	coord;

	if (!(frame = SDL_CreateRGBSurface(0, frame_len.w, frame_len.h,
					32, 0, 0, 0, 0)))
		return (0);
	SDL_FillRect(frame, 0, background_color);
	coord.x = 0;
	coord.y = 0;
	coord.w = frame_len.w;
	coord.h = len;
	SDL_FillRect(frame, &coord, frame_color);
	coord.y = frame_len.h - len;
	SDL_FillRect(frame, &coord, frame_color);
	coord.x = 0;
	coord.y = 0;
	coord.w = len;
	coord.h = frame_len.h;
	SDL_FillRect(frame, &coord, frame_color);
	coord.x = frame_len.w - len;
	SDL_FillRect(frame, &coord, frame_color);
	return (frame);
}

char		*ft_strtoupper(char *str)
{
	int n;

	n = -1;
	while (str[++n])
	{
		if (str[n] > 127)
			str[n] = 0;
		else
			str[n] = ft_toupper(str[n]);
	}
	return (str);
}

void		get_width(t_vm *vm, int *w, int *h, int choice)
{
	SDL_Surface **surface;

	surface = !choice ?
		vm->visu.champ_jauge_src : vm->visu.champ_jauge_halo_src;
	*w = (surface[0]->w * vm->visu.log_coord.w) / vm->visu.log_background->w;
	*h = (surface[0]->h * vm->visu.log_coord.h) / vm->visu.log_background->h;
}
