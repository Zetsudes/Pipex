/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:04:20 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 15:24:57 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dest[i] && i < n)
		i++;
	while (src[j] && i + j + 1 < n)
	{
		dest[i + j] = src[j];
		j++;
	}
	if (i < n)
		dest[i + j] = '\0';
	while (src[j])
		j++;
	return (i + j);
}
/*
int	main(void)
{
	char	src[] = "Hello";
	char	dest[10] = "hoho";
	int	size = sizeof(dest);

	int	lenght = ft_strlcat(dest, src, size);
	printf("Longueur de dest; %u", lenght);
	printf("Dest; %s", dest);
}
*/
