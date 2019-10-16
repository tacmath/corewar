/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 22:39:17 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/29 14:01:46 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

void	write_bytes(void *mem, size_t len, char byte)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = mem;
	i = 0;
	while (i < len)
	{
		ptr[i] = byte;
		i++;
	}
}

void	print_bytes(void *mem, int size, int pc)
{
	int				i;
	unsigned char	*ptr;

	ptr = mem;
	i = 0;
	while (i < size)
	{
		ft_printf("%02x ", *(ptr + (pc + i) % MEM_SIZE));
		i++;
	}
}

int		memdump(t_vm *vm)
{
	int n;
	int m;

	n = 0;
	while (n < MEM_SIZE)
	{
		ft_printf("0x%04x : ", n);
		m = n - 1;
		while (++m < n + 64 && m < MEM_SIZE)
			ft_printf("%02x ", vm->arena.mem[m]);
		ft_putchar('\n');
		n += 64;
	}
	if (vm->options.visu)
		quit_visu(vm);
	return (1);
}
