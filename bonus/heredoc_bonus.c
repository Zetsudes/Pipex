/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:40:22 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/29 15:40:27 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	create_heredoc_file(char *limiter)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("Heredoc creation failed", 1, NULL);
	ft_putstr_fd(HEREDOC_PROMPT, 1);
	line = get_next_line(0);
	while (line && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		ft_putstr_fd(line, fd);
		free(line);
		ft_putstr_fd(HEREDOC_PROMPT, 1);
		line = get_next_line(0);
	}
	if (line)
		free(line);
	close(fd);
	return (open(HEREDOC, O_RDONLY));
}

void	handle_heredoc(t_pipex *pipex)
{
	pipex->fd_infile = create_heredoc_file(pipex->limiter);
	if (pipex->fd_infile < 0)
	{
		unlink(HEREDOC);
		error_exit("Heredoc failed", 1, NULL);
	}
}
