/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:00:54 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/05 15:13:32 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <strings.h>
#include "libft.h"

void	*ft_bzero(void *str, size_t n)
{
	size_t	i;
	char	*str1;

	i = 0;
	str1 = str;
	while (i < n)
	{
		str1[i] = 0;
		i++;
	}
	return (str);
}
/*
int	main(void)
{
	char	str[] = "Salut les ploucs";
	char	str1[] = "Yo les nazes";

	ft_bzero(str, 4);
	bzero(str1, 4);
	printf("Mine : %s Real : %s", str, str1);

}
*/
