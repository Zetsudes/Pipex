/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:21:42 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/15 18:57:13 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
/*
int	main(void)
{
	char s1[] = "AAAA";
	char s2[] = "AAAZ";
	char s3[] = "Wesh";
	int n = 3;

	printf("ft_strncmp(s1, s2) = %d\n", ft_strncmp(s1, s2, n)); // 0
        printf("ft_strncmp(s1, s3) = %d\n", ft_strncmp(s1, s3, n)); //
        printf("ft_strncmp(s2, s3) = %d\n", ft_strncmp(s2, s3, n)); //

    	return 0;
}
*/
