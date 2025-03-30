/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:40:03 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/26 13:49:48 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_type(char specifier, va_list args)
{
	if (specifier == 'c')
		return (handle_char(va_arg(args, int)));
	else if (specifier == 's')
		return (handle_string(va_arg(args, char *)));
	else if (specifier == 'p')
		return (handle_pointer(va_arg(args, void *)));
	else if (specifier == 'd' || specifier == 'i')
		return (handle_number(va_arg(args, int)));
	else if (specifier == 'u')
		return (handle_unsigned(va_arg(args, unsigned int)));
	else if (specifier == 'x' || specifier == 'X')
		return (handle_hex(va_arg(args, unsigned int), specifier));
	else if (specifier == '%')
		return (handle_percent());
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			count += check_type(format[i], args);
		}
		else
		{
			write(1, &format[i], 1);
			count++;
		}
		i++;
	}
	va_end(args);
	return (count);
}
/*
int main(void)
{
	ft_printf(" MINE: %u\n", -1);
	printf(" OG:%u\n", -1);
	ft_printf(" MINE: %u\n", 10);
	printf(" OG: %u\n", 10);
}
*/
