/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_process1.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mtaquet <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/12 17:18:10 by mtaquet      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:29:03 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

static void	print_process_2(t_process ***process, int mem, t_vm *vm)
{
	free(*process);
	vm->visu.info_pages = 1;
	*process = get_process(mem, vm);
}

static void	print_process_3(t_process **process, int *process_num,
		int *old_mem, t_vm *vm)
{
	(*process_num)++;
	if (!process[*process_num])
		*process_num = 0;
	*old_mem = -1;
	vm->visu.info_pages = 1;
}

static void	print_process_4(t_process **process, int *process_num,
		int *old_mem, t_vm *vm)
{
	(*process_num)--;
	if (*process_num < 0)
		*process_num = get_max_process_num(process) - 1;
	*old_mem = -1;
	vm->visu.info_pages = 1;
}

static int	pp_5(int old_mem, int mem)
{
	return (!!(old_mem == -1 || old_mem != mem));
}

int			print_process(t_vm *vm, int mem, int status)
{
	static t_process	**process = 0;
	SDL_Rect			coord;
	int					r;
	static int			old_mem = -1;
	static int			process_num = 0;

	if (status == RESET && print_process_1(&process, &process_num, &old_mem))
		return (1);
	if (old_mem == -1 || old_mem != mem)
		print_process_2(&process, mem, vm);
	print_memory(vm);
	print_cycle(vm);
	r = ft_sqrt(MEM_SIZE);
	if (status == NEXT_PROCESS)
		print_process_3(process, &process_num, &old_mem, vm);
	if (status == PREVIOUS_PROCESS)
		print_process_4(process, &process_num, &old_mem, vm);
	coord = treat_coord(vm, (mem % r) * vm->visu.mem_len.w +
			vm->visu.memory_coord.x, (mem / r) * vm->visu.mem_len.h +
			vm->visu.memory_coord.y, vm->visu.info_pages == 1 ? 7 : 8);
	print_info_process(vm, coord, *(process[process_num]), pp_5(old_mem, mem));
	if (old_mem == -1 || old_mem != mem)
		old_mem = mem;
	SDL_UpdateWindowSurface(vm->visu.window);
	return (1);
}
