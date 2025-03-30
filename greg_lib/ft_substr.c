/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:01:21 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/15 19:17:39 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen((char *)s))
		return (ft_strdup(""));
	if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
int main(void)
{
    char *s;
    unsigned int i;
    size_t len;

    s = "Hello les ploucs";
    i = 3;
    len = 13;
    printf("%s", ft_substr(s, i, len));
}
*/
