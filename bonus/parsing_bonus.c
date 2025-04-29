/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:45:53 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/29 16:05:44 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	handle_arguments(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int	start_cmd;

	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->is_heredoc = 0;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		pipex->is_heredoc = 1;
		pipex->limiter = argv[2];
		start_cmd = 3;
	}
	else
		start_cmd = 2;
	pipex->cmd_count = argc - start_cmd - 1;
	pipex->cmds = malloc(sizeof(char **) * (pipex->cmd_count + 1));
	if (!pipex->cmds)
		error_exit("Memory allocation failed", 1, NULL);
	split_arg(pipex, start_cmd, argv);
}

void	handle_files(t_pipex *pipex)
{
	if (pipex->is_heredoc)
	{
		handle_heredoc(pipex);
		pipex->fd_outfile = open(pipex->argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else
	{
		pipex->fd_infile = open(pipex->argv[1], O_RDONLY);
		if (pipex->fd_infile < 0)
			perror(pipex->argv[1]);
		pipex->fd_outfile = open(pipex->argv[pipex->argc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (pipex->fd_outfile < 0)
		perror(pipex->argv[pipex->argc - 1]);
}

void	init_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc(sizeof(int *) * (pipex->cmd_count - 1));
	if (!pipex->pipes)
		error_exit("Memory allocation failed", 1, NULL);
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		pipex->pipes[i] = malloc(sizeof(int) * 2);
		if (!pipex->pipes[i])
		{
			pipex->pipes[i] = NULL;
			clean_up(pipex);
			error_exit("Memory allocation failed", 1, NULL);
		}
		if (pipe(pipex->pipes[i]) == -1)
		{
			clean_up(pipex);
			error_exit("Pipe creation failed", 1, NULL);
		}
		i++;
	}
}

int	execute_commands(t_pipex *pipex)
{
	t_exec	exec;

	init_pipes(pipex);
	exec.fd_in = pipex->fd_infile;
	exec.i = 0;
	while (exec.i < pipex->cmd_count)
		handle_child_process(pipex, &exec, exec.i++);
	close_pipes(pipex);
	exec.status = 0;
	while (exec.i-- > 0)
	{
		exec.waited_pid = waitpid(-1, &exec.temp_status, 0);
		if (exec.waited_pid == exec.last_pid)
			exec.status = exec.temp_status;
	}
	waitpid(exec.last_pid, &exec.status, 0);
	if (WIFEXITED(exec.status))
		return (WEXITSTATUS(exec.status));
	return (1);
}

void	handle_child_process(t_pipex *pipex, t_exec *exec, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		error_exit("Fork failed", 2, NULL);
	if (pid == 0)
	{
		if (i == pipex->cmd_count - 1)
			child_process(pipex, exec->fd_in, pipex->fd_outfile,
				pipex->cmds[i]);
		else
			child_process(pipex, exec->fd_in, pipex->pipes[i][1],
				pipex->cmds[i]);
	}
	if (i == pipex->cmd_count - 1)
		exec->last_pid = pid;
	if (i > 0 && exec->fd_in != pipex->fd_infile)
		close(exec->fd_in);
	if (i < pipex->cmd_count - 1)
	{
		close(pipex->pipes[i][1]);
		exec->fd_in = pipex->pipes[i][0];
	}
}
