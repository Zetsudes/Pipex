/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 08:22:40 by zamohame          #+#    #+#             */
/*   Updated: 2024/11/11 10:22:53 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			word_count++;
		i++;
	}
	return (word_count);
}

char	*allocate_word(char const *s, int start, int end)
{
	char	*word;

	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_memcpy(word, s + start, end - start);
	word[end - start] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	res = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!res || !s)
		return (NULL);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != c && s[i])
			i++;
		if (start < i)
			res[j++] = allocate_word(s, start, i);
	}
	res[j] = NULL;
	return (res);
}
/*
int main(void)
{
    char *s = "Hello les ploucs omg i hate you so much";
    char **res = ft_split(s, ' ');
    int i = 0;
    while (res[i])
    {
        printf("%s\n", res[i]);
        i++;
    }
    i = 0;
    while (res[i])
    {
        free(res[i]);
        i++;
    }
    free(res);

    return (0);
}
*/
