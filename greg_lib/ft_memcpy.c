/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:19:38 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 11:31:48 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*dest1;
	const char	*src1;

	i = 0;
	dest1 = dest;
	src1 = src;
	while (i < n)
	{
		dest1[i] = src1[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	dest[100];
	char	src[] = "Wesh morray";
	ft_memcpy(dest, src, 4);
	printf("Dest : %s", dest);

}
*/
