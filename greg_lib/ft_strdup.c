/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:50:17 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/12 18:36:48 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	char	*coeur;
	int		len;

	len = ft_strlen(src);
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	coeur = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (coeur);
}
/*
int	main(void)
{
	char	*dest;
	char src[] = "Il faut sachez que";
	dest = ft_strdup(src);
	printf("Dest : %s", dest);
	free(dest);
}
*/
