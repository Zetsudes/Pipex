/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:01:59 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 18:26:38 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t items, size_t n)
{
	size_t	total_size;
	void	*ptr;

	if (items == 0 || n == 0)
		return (malloc(1));
	total_size = items * n;
	if (n != 0 && (total_size / n != items))
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
	return (ptr);
}
/*
int	main(void)
{
	int numItems = 15;
	int *myArray = calloc(numItems, sizeof(int));

	for(int i = 0; i < numItems; i++) 
	{
  		myArray[i] = i + 1;
	}

	for(int i = 0; i < numItems; i++) 
	{
  		printf("%d ", myArray[i]);
	}
	free(myArray);
	myArray = NULL;
}
*/
