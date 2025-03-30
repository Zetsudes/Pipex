/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:29:17 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/26 14:04:02 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_pointer(unsigned long *ptr)
{
	int	len;

	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	len = handle_hex((unsigned long)ptr, 'x');
	return (2 + len);
}
