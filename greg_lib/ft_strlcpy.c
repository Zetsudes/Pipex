/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:42:58 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 15:32:09 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	len_src;
	char	*s;

	i = 0;
	s = (char *) src;
	len_src = ft_strlen(s);
	if (n == 0)
		return (len_src);
	while (src[i] && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (dest[i])
		dest[i] = '\0';
	return (len_src);
}
/*
int	main(void)
{
	char	src[] = "Hello";
	char	dest[10];
	int	size = sizeof(dest);

	int	length = ft_strlcpy(dest, src, size);
	printf("Longueur de dest: %u\n", length);
	printf("Dest: %s\n", dest);

	return 0;
}
*/
