/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:39:17 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 13:14:36 by mtaquet     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int		print_usage(void)
{
	ft_dprintf(2, "usage: ./corewar [-vg] [-d nbr_cycles] [[-n number] ");
	ft_dprintf(2, "champion1.cor]. Max players: %d\n", MAX_PLAYERS);
	return (0);
}

void	set_champs(t_vm *vm)
{
	int interval;
	int i;

	interval = MEM_SIZE / vm->nb_champs;
	i = 0;
	while (i < vm->nb_champs)
	{
		vm->champs_decoded[i].start = i * interval;
		ft_memcpy(vm->arena.mem + i * interval, vm->champs_decoded[i].prog,
		vm->champs_decoded[i].header.prog_size);
		write_bytes(vm->arena.champs + i * interval,
		vm->champs_decoded[i].header.prog_size, vm->champs_decoded[i].visu_id);
		i++;
	}
}

void	init_vm(t_vm *vm)
{
	ft_bzero(vm, sizeof(*vm));
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->last_live = -1;
	vm->options.verbose = 0;
	vm->options.visu = 0;
	vm->options.cycle_dump = -1;
}

int		main(int ac, char **av)
{
	t_vm	vm;
	int		ret;

	init_vm(&vm);
	if (!get_options(ac - 1, av + 1, &vm.options))
		return (print_usage());
	vm.nb_champs = vm.options.nb_champs;
	if (!vm.nb_champs || vm.nb_champs > MAX_PLAYERS)
		return (print_usage());
	if (MEM_SIZE / vm.nb_champs < CHAMP_MAX_SIZE)
		return (!!ft_dprintf(2,
		"an arena of %d bytes is not enough to host all players\n", MEM_SIZE));
		if (!(vm.champs_decoded =
		parser(vm.options.players_file, vm.nb_champs, vm.options.num_champs)))
		return (1);
	if (vm.options.visu && !(vm.visu.path = get_exec_path(av[0])))
		return (1);
	set_champs(&vm);
	if (vm.options.visu && !init_visu(&vm))
		return (1);
	ret = corewar(&vm);
	if (vm.options.visu)
		quit_visu(&vm);
	clean(&vm);
	return (ret);
}
