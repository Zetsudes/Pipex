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

void    handle_arguments(int argc, char **argv, char ***cmd1, char ***cmd2)
{
    *cmd1 = ft_split(argv[2], " ");
    *cmd2 = ft_split(argv[3], " ");
}

void    handle_files(int argc, char **argv, int *fd_infile, int *fd_outfile, int fd[2])
{
    if (pipe(fd) == -1)
        error_exit("Pipe creation failed :(", 1);
    *fd_infile = open(argv[1], O_RDONLY);
    *fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_infile < 0 || fd_outfile < 0)
        error_exit("File error : (", 1);
}

void	child_process(int fd_infile, int fd_outfile, char **cmd, char **envp)
{
	if (dup2(fd_infile, STDIN_FILENO) == -1)
        error_exit("Dup2 failed :(", 1);
    if (dup2(fd_outfile, STDOUT_FILENO) == -1)
        error_exit("Dup2 failed :(", 1);
    execve(fd_infile, cmd, **envp);
    error_exit("Execve failed :(", 1);
}

void    execute_commands(int fd[2], int fd_infile, int fd_outfile, char **cmd1, char **cmd2, char **envp)
{
    int pid1;
    int pid2;

    pid1 = fork();
    if (pid1 < 0)
        error_exit("Oopsie fork failed :(", 2);
    if (pid1 == 0)
        child_process(fd_infile, fd[1], **cmd1, **envp); 
    close(fd[1]);
    pid2 = fork();
    if (pid2 < 0)
        error_exit("Oopsie fork failed :( ", 2);
    if (pid2 == 0)
        child_process(fd[0], fd_outfile, **cmd2, **envp);
    close(fd[0]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}
