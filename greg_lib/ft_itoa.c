/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:28:05 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 14:19:18 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static char	*reverse(char *str)
{
	char	tmp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(str) - 1;
	if (str[0] == '-')
		i++;
	while (j > i)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

static int	count_digits(long num)
{
	int	count;

	count = 0;
	if (num <= 0)
		count = 1;
	while (num)
	{
		num /= 10;
		count++;
	}
	return (count);
}

static char	*handle_special_cases(int n)
{
	char	*res;

	if (n == 0)
	{
		res = malloc(2);
		if (!res)
			return (NULL);
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	if (n == -2147483648)
	{
		res = malloc(12);
		if (!res)
			return (NULL);
		ft_memcpy(res, "-2147483648", 12);
		return (res);
	}
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	long	num;

	num = n;
	i = 0;
	res = handle_special_cases(n);
	if (res)
		return (res);
	res = malloc((count_digits(num) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	if (num < 0)
	{
		res[i++] = '-';
		num = -num;
	}
	while (num)
	{
		res[i++] = (num % 10) + '0';
		num /= 10;
	}
	res[i] = '\0';
	return (reverse(res));
}
/*
int main()
{
    int num1 = -152;
    int num2 = -2147483648;
    int num3 = 0;

char *str1 = ft_itoa(num1);
    char *str2 = ft_itoa(num2);
    char *str3 = ft_itoa(num3);

    printf("-152: %s\n", str1);
    printf("-2147483648: %s\n", str2);
    printf("0: %s\n", str3);

    return 0;
}
*/
