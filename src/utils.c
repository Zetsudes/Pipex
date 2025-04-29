/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:46:44 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/28 12:52:18 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_exit(const char *msg, int exit_code, void *to_free)
{
	if (errno)
		perror(msg);
	else
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	if (to_free)
		free(to_free);
	exit(exit_code);
}

void	handle_error(int argc, char **argv)
{
	if (argc != 5)
		error_exit("Usage: ./pipex infile cmd1 cmd2 outfile", 1, NULL);
	if (access(argv[1], R_OK) == -1)
		perror(argv[1]);
	if (access(argv[argc - 1], W_OK) == -1 && access(argv[argc - 1], F_OK) == 0)
		perror(argv[argc - 1]);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	clean_up(t_pipex *pipex)
{
	if (pipex->cmd1)
		free_tab(pipex->cmd1);
	if (pipex->cmd2)
		free_tab(pipex->cmd2);
}

void	fork_error(t_pipex *pipex, pid_t pid, int flag)
{
	if (pid < 0)
	{
		if (flag == 1)
			close(pipex->fd[0]);
		error_exit("Error: fork failed", 2, NULL);
	}
}
