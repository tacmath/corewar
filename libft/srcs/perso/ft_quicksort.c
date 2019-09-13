/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_quicksort.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/06/19 14:17:59 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/19 14:19:58 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static void	swap_mem(char *s1, char *s2, int size)
{
	char	tmp[size];
	int		n;

	n = -1;
	while (++n < size)
		tmp[n] = s1[n];
	n = -1;
	while (++n < size)
		s1[n] = s2[n];
	n = -1;
	while (++n < size)
		s2[n] = tmp[n];
}

void		ft_quicksort(void *tab, int len,
		int type_size, int (*cmp)(void*, void*))
{
	char	*mem;
	char	*compa;
	int		n;
	int		m;

	if (len < 2)
		return ;
	mem = (char*)tab;
	compa = &mem[(len - 1) * type_size];
	m = 0;
	n = -1;
	while (++n < len)
		if (cmp(&mem[n * type_size], compa) <= 0)
		{
			if (m != n)
				swap_mem(&mem[n * type_size], &mem[m * type_size], type_size);
			m++;
		}
	ft_quicksort(mem, --m, type_size, cmp);
	ft_quicksort(&mem[m * type_size], len - m, type_size, cmp);
}
