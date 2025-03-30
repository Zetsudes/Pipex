/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:12:31 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/06 17:23:39 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void	*ft_memset(void *str, int a, size_t n)
{
	size_t	i;
	char	*str1;

	i = 0;
	str1 = str;
	while (i < n)
	{
		str1[i] = a;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[] = "Salut les ploucs";
	ft_memset(str, '!', 4);
	printf("%s", str);
}
*/
