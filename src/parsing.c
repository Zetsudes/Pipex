/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:45:53 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/08 13:24:07 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

void    handle_arguments(t_pipex *pipex)
{
    pipex->cmd1 = ft_split(pipex->argv[2], " ");
    pipex->cmd2 = ft_split(pipex->argv[3], " ");
}

void    handle_files(t_pipex *pipex)
{
    if (pipe(pipex->fd) == -1)
        error_exit("Pipe creation failed :(", 1);
    pipex->fd_infile = open(pipex->argv[1], O_RDONLY);
    pipex->fd_outfile = open(pipex->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->fd_infile < 0 || pipex->fd_outfile < 0)
        error_exit("File error :(", 1);
}

void	child_process(int fd_infile, int fd_outfile, char **cmd, char **envp)
{
    char *path;
	if (dup2(fd_infile, STDIN_FILENO) == -1)
        error_exit("Dup2 failed :(", 1);
    if (dup2(fd_outfile, STDOUT_FILENO) == -1)
        error_exit("Dup2 failed :(", 1);
    path = get_path(cmd[0], envp);
    if (!path)
		error_exit("Command not found :(", 127);
    execve(path, cmd, envp);
    error_exit("Execve failed :(", 1);
}

void    execute_commands(t_pipex *pipex)
{
    pid_t pid1;
    pid_t pid2;

    pid1 = fork();
    if (pid1 < 0)
        error_exit("Oopsie fork failed :(", 2);
    if (pid1 == 0)
        child_process(pipex->fd_infile, pipex->fd[1], pipex->cmd1, pipex->envp); 
    close(pipex->fd[1]);
    pid2 = fork();
    if (pid2 < 0)
        error_exit("Oopsie fork failed :( ", 2);
    if (pid2 == 0)
        child_process(pipex->fd[0], pipex->fd_outfile, pipex->cmd2, pipex->envp);
    close(pipex->fd[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
