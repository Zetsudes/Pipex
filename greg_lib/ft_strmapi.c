/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:50:32 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/11 10:27:37 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len_s;
	char			*res;

	if (!s || !f)
		return (NULL);
	i = 0;
	len_s = ft_strlen((char *)s);
	res = (char *)malloc((len_s + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len_s)
	{
		res[i] = (*f)(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
char	f(unsigned int i, char c)
{
	c += i;
	return (c);
}

int	main()
{
	char	str[] = "aaaaaa1";

	printf("%s\n", ft_strmapi(str, &f));
}
*/
