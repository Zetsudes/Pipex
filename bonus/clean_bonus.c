/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:08:40 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/29 16:05:48 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	clean_up(t_pipex *pipex)
{
	int	i;

	if (pipex->cmds)
	{
		i = 0;
		while (i < pipex->cmd_count && pipex->cmds[i])
		{
			free_tab(pipex->cmds[i]);
			i++;
		}
		free(pipex->cmds);
	}
	if (pipex->pipes)
	{
		i = 0;
		while (i < pipex->cmd_count - 1 && pipex->pipes[i])
		{
			free(pipex->pipes[i]);
			i++;
		}
		free(pipex->pipes);
	}
	if (pipex->is_heredoc)
		unlink(HEREDOC);
}

void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][0]);
		close(pipex->pipes[i][1]);
		i++;
	}
}
