/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:39:46 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 18:42:21 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int	is_char_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len_s1;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	if (*set == '\0')
		return (ft_strdup((char *)s1));
	i = 0;
	while (s1[i] && is_char_set(s1[i], set))
		i++;
	len_s1 = ft_strlen((char *)s1);
	j = len_s1 - 1;
	if (i == len_s1)
		return (ft_strdup(""));
	while (j > i && is_char_set(s1[j], set))
		j--;
	res = malloc(sizeof(char) * (j - i + 2));
	if (!res)
		return (NULL);
	ft_memcpy(res, s1 + i, j - i + 1);
	res[j - i + 1] = '\0';
	return (res);
}
/*
int main(void)
{
    char *s;
    char *c;

    s = "lllllHello les ploucslll";
    c = "l";
    printf("%s\n", ft_strtrim(s, c));

    return 0;
}
*/
