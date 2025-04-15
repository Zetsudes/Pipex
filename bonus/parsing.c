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

#include "../include/pipex_bonus.h"

void	handle_arguments(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int i;

	i = 0;
	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmds = (char ***)malloc(sizeof(char **) * (argc - 3 + 1));
	if (!pipex->cmds)
		error_exit("Malloc failed :(", 1);
	while (i < pipex->argc - 3)
	{
		pipex->cmds[i] = ft_split(pipex->argv[i + 2], ' ');
		i++;
	}
	pipex->cmds[i] = NULL;
}

void	handle_pipes(t_pipex *pipex)
{
	int i;

	pipex->cmd_count = pipex->argc - 3;
	pipex->pipes = malloc(sizeof(int[2]) * (pipex->cmd_count - 1));
	if (!pipex->pipes)
		error_exit("Malloc failed :(", 1, NULLs);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
			error_exit("Malloc failed :(", 1, pipex->pipes);
		if (pipe(pipex->pipes[i]) == -1)
			error_exit("Pipe failed :(", 1, pipex->pipes);
		i++;
	}
}

void	child_process(int fd_infile, int fd_outfile, char **cmd, char **envp)
{
	char	*path;

	if (dup2(fd_infile, STDIN_FILENO) == -1 || dup2(fd_outfile, STDOUT_FILENO) == -1)
        error_exit("dup2 failed :(", 1, cmd);
	path = get_path(cmd[0], envp);
	if (!path)
		error_exit(cmd[0], 127);
	execve(path, cmd, envp);
	error_exit("Execve failed :(", 1);
}

void	fork_child(t_pipex *pipex, int in, int out, char **cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Oopsie fork failed :(", 2);
	if (pid == 0)
	{
		if (in != -1)
			close(pipex->fd[0]);
		if (out != -1)
			close(pipex->fd[1]);
		child_process(in, out, cmd, pipex->envp);
	}
}

int	execute_commands(t_pipex *pipex)
{
	int	i;
	int	status;

	i = 0;
	fork_child(pipex, pipex->fd_infile, pipex->fd[1], pipex->cmds[i]);
	close(pipex->fd[1]);
	while (i < pipex->cmd_count - 2)
	{
		pipex->fd[0] = pipex->pipes[i][0];
		pipex->fd[1] = pipex->pipes[i][1];
		fork_child(pipex, pipex->fd[0], pipex->fd[1], pipex->cmds[i + 1]);
		close(pipex->fd[0]);
		close(pipex->fd[1]); 
		i++;
	}
	fork_child(pipex, pipex->fd[0], pipex->fd_outfile, pipex->cmds[i]);
	close(pipex->fd[0]);
	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

// int	execute_commands(t_pipex *pipex)
// {
// 	int	status;

// 	fork_child(pipex, pipex->fd_infile, pipex->fd[1], pipex->cmd1);
// 	close(pipex->fd[1]);
// 	fork_child(pipex, pipex->fd[0], pipex->fd_outfile, pipex->cmd2);
// 	close(pipex->fd[0]);
// 	wait(NULL);
// 	waitpid(-1, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }

