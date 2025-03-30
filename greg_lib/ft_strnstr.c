/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:20:46 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/06 13:43:14 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	if (!*to_find)
		return ((char *)str);
	i = 0;
	while (i < n && str[i])
	{
		j = 0;
		while (i + j < n && str[i + j] == to_find[j] && to_find[j] != '\0')
		{
			j++;
		}
		if (to_find[j] == '\0')
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
char	str[] = "Pas comme ca Zinedine";
char	to_find[] = "Zin";
char	*res = ft_strnstr(str, to_find, 16);
printf("%s", res);
}
*/
