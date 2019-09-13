/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_swap.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/06 10:32:04 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/12 17:58:54 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	unsigned char	*tmpa;
	unsigned char	*tmpb;
	size_t			i;

	i = 0;
	if (a == b)
		return ;
	tmpa = (unsigned char *)a;
	tmpb = (unsigned char *)b;
	while (i < size)
	{
		tmpa[i] = tmpa[i] ^ tmpb[i];
		tmpb[i] = tmpb[i] ^ tmpa[i];
		tmpa[i] = tmpa[i] ^ tmpb[i];
		i++;
	}
}

void	*mem_swap(void *mem, int size)
{
	uint16_t *mem16;
	uint32_t *mem32;

	if (size == 2)
	{
		mem16 = (uint16_t *)(mem);
		*mem16 = (*mem16 >> 8 | *mem16 << 8);
		return (mem16);
	}
	if (size == 4)
	{
		mem32 = (uint32_t *)(mem);
		*mem32 = ((*mem32 >> 24) & 0xff) | ((*mem32 << 8) & 0xff0000) |
			((*mem32 >> 8) & 0xff00) | ((*mem32 << 24) & 0xff000000);
		return (mem32);
	}
	return (mem);
}
