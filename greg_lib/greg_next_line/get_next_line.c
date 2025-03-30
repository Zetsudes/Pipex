/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:23:23 by zamohame          #+#    #+#             */
/*   Updated: 2024/12/09 15:37:39 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *extract_line(char *buffer)
{
	int i;
	char *line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char *save_remainder(char *buffer)
{
	int i;
	int j;
	char *remainder;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	remainder = malloc(ft_strlen(buffer) - i);
	if (!remainder)
		return (NULL);
	i++;
	j = 0;
	while (buffer[i])
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	if (*remainder == '\0')
	{
		free(remainder);
		remainder = NULL;
	}
	return (remainder);
}

char *get_next_line(int fd)
{
	static char *buffer = NULL;
	char *line;
	char *temp;
	char *bjr;
	int bytes_read;

	temp = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(temp);
		return (NULL);
	}
	if (!buffer)
		buffer = ft_strdup("");
	while (!ft_strchr(buffer, '\n') && (bytes_read = read(fd, temp,
														  BUFFER_SIZE)) > 0)
	{
		temp[bytes_read] = '\0';
		bjr = buffer;
		buffer = ft_strjoin(buffer, temp);
		free(bjr);
		if (!buffer)
		{
			free(temp);
			return (NULL);
		}
	}
	if (!buffer || *buffer == '\0')
	{
		free(temp);
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(buffer);
	buffer = save_remainder(buffer);
	free(temp);
	return (line);
}