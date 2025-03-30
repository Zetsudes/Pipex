/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:41:46 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/26 14:04:41 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>

int	ft_printf(const char *format, ...);
int	handle_char(char c);
int	handle_string(char *str);
int	handle_number(int n);
int	handle_pointer(unsigned long *ptr);
int	handle_unsigned(unsigned int n);
int	handle_hex(unsigned long n, char format);
int	handle_percent(void);

#endif
