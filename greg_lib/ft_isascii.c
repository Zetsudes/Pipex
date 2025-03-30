/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:38:12 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/11 13:35:16 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"

int	ft_isascii(int b)
{
	if (!(b >= 0 && b <= 127))
		return (0);
	else
		return (1);
}
/*
int	main(void)
{
	char	b;

	b = 'h';
	printf("%d", ft_isascii(b));
}
*/