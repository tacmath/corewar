/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strchr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: lperron <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 10:05:46 by lperron      #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 10:13:10 by lperron     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	i = -1;
	while (s[++i] != '\0')
		if ((int)s[i] == c)
			return ((char *)&s[i]);
	if (c == (int)'\0')
		return ((char *)&s[i]);
	return (NULL);
}
