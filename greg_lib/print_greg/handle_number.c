/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_number.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:04:45 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/26 14:03:28 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>

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

static int	handle_int_min(void)
{
	write(1, "-2147483648", 11);
	return (11);
}

static int	convert_to_string(int n, char *buffer)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		buffer[i++] = (n % 10) + '0';
		n /= 10;
	}
	return (i);
}

int	handle_number(int n)
{
	char	buffer[20];
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	if (n == INT_MIN)
		return (handle_int_min());
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		count++;
	}
	i = convert_to_string(n, buffer);
	print_digits(buffer, i);
	return (i + count);
}
