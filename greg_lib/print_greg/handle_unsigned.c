/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:35:42 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/26 13:41:44 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_digits(char *buffer, int size)
{
	int	i;

	i = size - 1;
	while (i >= 0)
	{
		write(1, &buffer[i], 1);
		i--;
	}
}

int	handle_unsigned(unsigned int n)
{
	char	buffer[10];
	int		i;

	i = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (n > 0)
	{
		buffer[i] = (n % 10) + '0';
		i++;
		n /= 10;
	}
	print_digits(buffer, i);
	return (i);
}
