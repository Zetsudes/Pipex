/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:45:53 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/12 16:47:53 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	handle_arguments(t_pipex *pipex, int argc, char **argv, char **envp)
{
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd1 = ft_split(pipex->argv[2], ' ');
	pipex->cmd2 = ft_split(pipex->argv[3], ' ');
}

void	handle_files(t_pipex *pipex)
{
	if (pipe(pipex->fd) == -1)
		error_exit("Pipe creation failed :(", 1);
	pipex->fd_infile = open(pipex->argv[1], O_RDONLY);
	pipex->fd_outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC,
			0644);
}

void	child_process(t_pipex *pipex, int fd_infile, int fd_outfile, char **cmd)
{
	char	*path;

	if (dup2(fd_infile, STDIN_FILENO) == -1 || dup2(fd_outfile, STDOUT_FILENO) == -1)
	{	clean_up(pipex);
		error_exit("dup2 failed :(", 1);
	}
	path = get_path(cmd[0], pipex->envp);
	if (!path)
	{	clean_up(pipex);
		error_exit(cmd[0], 127);
	}
	execve(path, cmd, pipex->envp);
	free(path);
	clean_up(pipex);
	error_exit("Execve failed :(", 1);
}

int	execute_commands(t_pipex *pipex)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	pid1 = fork();
	if (pid1 < 0)
		error_exit("Oopsie fork failed :(", 2);
	if (pid1 == 0)
	{
		close(pipex->fd[0]);
		child_process(pipex, pipex->fd_infile, pipex->fd[1], pipex->cmd1);
	}
	close(pipex->fd[1]);
	pid2 = fork();
	if (pid2 < 0)
		error_exit("Oopsie fork failed :( ", 2);
	if (pid2 == 0)
	{
		close(pipex->fd[1]);
		child_process(pipex, pipex->fd[0], pipex->fd_outfile, pipex->cmd2);
	}
	close(pipex->fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}
