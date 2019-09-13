/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnjoin.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: rcepre <rcepre@student.42.fr>              +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 07:02:10 by rcepre       #+#   ##    ##    #+#       */
/*   Updated: 2018/11/25 19:27:30 by rcepre      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
	int		len;
	char	*str;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strndup(s2, n));
	i = 0;
	len = ft_strlen(s1);
	if (!(str = ft_strnew(len + n)))
		return (NULL);
	len = 0;
	while (s1[len])
		str[i++] = s1[len++];
	len = 0;
	while (len < n && s2[len])
		str[i++] = s2[len++];
	return (str);
}
