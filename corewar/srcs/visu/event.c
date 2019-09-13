/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   event.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/08/14 10:55:43 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/09 17:09:36 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	get_event2(t_vm *vm, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_MINUS
			&& vm->visu.speed > -64)
	{
		if (vm->visu.speed < 1)
			vm->visu.speed *= 2;
		else if (vm->visu.speed > 1)
			vm->visu.speed /= 2;
		else
			vm->visu.speed = -2;
	}
	else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_r)
		vm->visu.speed = 1;
	else if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
		pause_visu(vm);
}

void	get_event(t_vm *vm)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if ((event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
				|| event.window.event == SDL_WINDOWEVENT_CLOSE)
			quit_visu(vm);
		if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			resize_window(vm, event.window.data1, event.window.data2);
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_KP_PLUS
				&& vm->visu.speed < 64)
		{
			if (vm->visu.speed < 1)
				vm->visu.speed /= 2;
			else
				vm->visu.speed *= 2;
			if (vm->visu.speed == -1)
				vm->visu.speed = 1;
		}
		else
			get_event2(vm, event);
	}
}
