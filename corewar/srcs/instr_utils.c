/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   instr_utils.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/07/27 21:18:43 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/07/27 21:21:14 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/corewar.h"

int			get_mempos(int nbr)
{
	nbr %= MEM_SIZE;
	if (nbr < 0)
		nbr += MEM_SIZE;
	return (nbr);
}

void		*memload(void *dst, void *src, size_t n, int off)
{
	size_t		i;
	char		*out;
	char		*in;

	i = 0;
	in = src;
	out = dst;
	while (i < n)
	{
		out[i] = in[(i + off) % MEM_SIZE];
		i++;
	}
	return (dst);
}

void		memstore(void *arena, void *src, size_t n, size_t off)
{
	size_t		i;
	char		*in;
	char		*mem;

	i = 0;
	in = src;
	mem = arena;
	while (i < n)
	{
		mem[(i + off) % MEM_SIZE] = in[i];
		i++;
	}
}

void		memsetcir(void *arena, char src, int n, int off)
{
	int		i;
	char	*mem;

	mem = arena;
	i = 0;
	while (i < n)
	{
		mem[(i + off) % MEM_SIZE] = src;
		i++;
	}
}
