/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:56:58 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 15:47:24 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strchr(const char *str, int a)
{
	int	i;

	i = 0;
	if (a < 0 || a > 255)
		return ((char *)str);
	while (str[i] && str[i] != a)
		i++;
	if (str[i] == a)
		return ((char *)&str[i]);
	return (NULL);
}
/*
int	main(void)
{
	char	str[] = "Hello les ploucs";
	char	*res = ft_strchr(str, 'z' + 256);
	printf("%s", res);
}
*/
