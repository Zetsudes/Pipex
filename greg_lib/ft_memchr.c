/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:25:37 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/06 12:57:33 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memchr(const void *s, int a, size_t n)
{
	const unsigned char	*ptr;
	size_t				i;

	ptr = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)a)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Hello les ploucs";
	char	*res = ft_memchr(str, 'l', 16);
	printf("%s", res);
}
*/
