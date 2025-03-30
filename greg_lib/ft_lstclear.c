/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:52:00 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/15 16:06:24 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;
	t_list	*next;

	cur = *lst;
	while (cur)
	{
		next = cur->next;
		ft_lstdelone(cur, del);
		cur = next;
	}
	*lst = NULL;
}
