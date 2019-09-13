/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_cor.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <lperron@student.le-101.f>         +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/09/07 17:39:30 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2019/09/07 17:39:48 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "corewar.h"

int				check_cor(char *filename)
{
	int len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strcmp(&filename[len - 4], ".cor"))
		return (0);
	return (1);
}
