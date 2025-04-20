/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:45:53 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/20 20:56:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void    handle_arguments(t_pipex *pipex, int argc, char **argv, char **envp)
{
    int i;
    int start_cmd;

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
    
    i = 0;
    while (i < pipex->cmd_count)
    {
        pipex->cmds[i] = ft_split(argv[i + start_cmd], ' ');
        if (!pipex->cmds[i])
        {
            pipex->cmds[i] = NULL;
            clean_up(pipex);
            error_exit("Memory allocation failed", 1, NULL);
        }
        i++;
    }
    pipex->cmds[i] = NULL;
}

void    handle_files(t_pipex *pipex)
{
    if (pipex->is_heredoc)
    {
        handle_heredoc(pipex);
        pipex->fd_outfile = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    else
    {
        pipex->fd_infile = open(pipex->argv[1], O_RDONLY);
        if (pipex->fd_infile < 0)
            perror(pipex->argv[1]);
        
        pipex->fd_outfile = open(pipex->argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }
    
    if (pipex->fd_outfile < 0)
        perror(pipex->argv[pipex->argc - 1]);
}

void    init_pipes(t_pipex *pipex)
{
    int i;

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

void    close_pipes(t_pipex *pipex)
{
    int i;

    i = 0;
    while (i < pipex->cmd_count - 1)
    {
        close(pipex->pipes[i][0]);
        close(pipex->pipes[i][1]);
        i++;
    }
}
int execute_commands(t_pipex *pipex)
{
    int     i;
    pid_t   pid;
    pid_t   last_pid; // Save last command's pid
    int     status;
    int     fd_in;

    init_pipes(pipex);
    i = 0;
    fd_in = pipex->fd_infile;

    while (i < pipex->cmd_count)
    {
        pid = fork();
        if (pid < 0)
            error_exit("Fork failed", 2, NULL);
        if (pid == 0)
        {
            if (i == pipex->cmd_count - 1)
                child_process(pipex, fd_in, pipex->fd_outfile, pipex->cmds[i]);
            else
                child_process(pipex, fd_in, pipex->pipes[i][1], pipex->cmds[i]);
        }

        if (i == pipex->cmd_count - 1)
            last_pid = pid; // Track last command's PID

        if (i > 0 && fd_in != pipex->fd_infile)
            close(fd_in);

        if (i < pipex->cmd_count - 1)
        {
            close(pipex->pipes[i][1]);
            fd_in = pipex->pipes[i][0];
        }

        i++;
    }

    close_pipes(pipex);

    // Wait for all children to finish
    i = 0;
    while (i++ < pipex->cmd_count)
        waitpid(-1, &status, 0);

    // Get the exit status of the last command
    waitpid(last_pid, &status, 0);
    return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}