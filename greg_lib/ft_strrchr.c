/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:25:14 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 16:03:53 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

char	*ft_strrchr(const char *str, int a)
{
	char			*res;
	char			c;
	unsigned int	i;

	c = (char) a;
	res = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			res = (char *)&str[i];
		i++;
	}
	if (str[i] == c)
		return ((char *)&str[i]);
	return (res);
}
/*
int	main(void)
{
	char	str[] = "Hello les ploucs";
	char	*res = ft_strrchr(str, 'o');
	printf("%s", res);
}
*/
