/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strndup.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rcepre <rcepre@student.42.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 07:38:03 by rcepre       #+#   ##    ##    #+#       */
/*   Updated: 2018/12/12 12:21:04 by rcepre      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char		*strcpy;
	size_t		i;

	i = -1;
	if (!((strcpy = (char*)ft_memalloc(sizeof(char) * ft_strlen(s) + 1))))
		return (NULL);
	while (s[++i] && i < n)
		strcpy[i] = s[i];
	strcpy[i] = '\0';
	return (strcpy);
}
