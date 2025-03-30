/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:21:08 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/26 13:59:41 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	length_hex(unsigned long n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

static void	print_hex(unsigned long n, const char format)
{
	char	c;

	if (n >= 16)
	{
		print_hex(n / 16, format);
		print_hex(n % 16, format);
	}
	else
	{
		if (n <= 9)
			c = (n + '0');
		else
		{
			if (format == 'x')
				c = (n - 10 + 'a');
			if (format == 'X')
				c = (n - 10 + 'A');
		}
		write(1, &c, 1);
	}
}

int	handle_hex(unsigned long n, const char format)
{
	if (n == 0)
		return (write(1, "0", 1));
	else
		print_hex(n, format);
	return (length_hex(n));
}
