/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:39:17 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/17 15:26:35 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	verbose_begin(t_vm *vm)
{
	int i;

	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < vm->nb_champs)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", i + 1,
		vm->champs_decoded[i].header.prog_size,
		vm->champs_decoded[i].header.prog_name,
		vm->champs_decoded[i].header.how);
	}
}

void	verbose_end(t_vm *vm)
{
	if (vm->last_live == -1)
		ft_printf("Draw\n");
	else
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
		vm->champs_decoded[vm->last_live].id,
		vm->champs_decoded[vm->last_live].header.prog_name);
	}
	if (vm->options.visu)
		print_end(vm, "WinnerCoreWar.png", "TRON.ttf");
}

void	print_adv(int size_instr, void *mem, int pc)
{
	ft_printf("ADV %d (0x%04x -> 0x%04x) ", size_instr, pc, (pc + size_instr));
	print_bytes(mem, size_instr, pc);
	ft_printf("\n");
}
