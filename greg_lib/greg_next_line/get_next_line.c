/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:23:23 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/29 16:49:23 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

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

char	*save_remainder(char *buffer)
{
	int		i;
	int		j;
	char	*remainder;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i] || buffer[i + 1] == '\0')
		return (free_buffer(buffer));
	remainder = malloc(ft_strlen(buffer) - i);
	if (!remainder)
		return (free_buffer(buffer));
	i++;
	j = 0;
	while (buffer[i])
		remainder[j++] = buffer[i++];
	remainder[j] = '\0';
	free(buffer);
	return (remainder);
}

char	*free_buffer(char *buffer)
{
	if (buffer)
		free(buffer);
	return (NULL);
}

int	handle_line(int fd, char **buffer, char *temp)
{
	int		bytes_read;
	char	*bjr;

	bytes_read = 0;
	while (!ft_strchr(*buffer, '\n'))
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if ((bytes_read) <= 0)
			break ;
		temp[bytes_read] = '\0';
		bjr = *buffer;
		*buffer = ft_strjoin(*buffer, temp);
		free(bjr);
		if (!*buffer)
		{
			free(temp);
			return (-1);
		}
	}
	if (bytes_read == -1)
		return (-1);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;
	char		*temp;

	temp = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || BUFFER_SIZE <= 0 || !temp)
	{
		free(temp);
		return (NULL);
	}
	if (!buffer)
		buffer = ft_strdup("");
	handle_line(fd, &buffer, temp);
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
