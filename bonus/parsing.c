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

	pipex->argc = argc;
	pipex->argv = argv;
	pipex->envp = envp;
	pipex->cmd_count = argc - 3;
	pipex->cmds = malloc(sizeof(char **) * (pipex->cmd_count + 1));
	if (!pipex->cmds)
		error_exit("Malloc failed :(", 1);
	i = 0;
	while (i < pipex->cmd_count)
	{
		pipex->cmds[i] = ft_split(pipex->argv[i + 2], ' ');
		i++;
	}
	pipex->cmds[i] = NULL;
}

void handle_files(t_pipex *pipex) {
    pipex->fd_infile = open(pipex->argv[1], O_RDONLY);
    if (pipex->fd_infile < 0) {
        // Handle non-existing input file specifically
        pipex->input_file_error = true;
        perror(pipex->argv[1]);
    }
    
    pipex->fd_outfile = open(pipex->argv[pipex->argc - 1],
        O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex->fd_outfile < 0) {
        clean_up(pipex);
        perror(pipex->argv[pipex->argc - 1]);
        exit(1);
    }
}

void	child_process(t_pipex *pipex, int fd_infile, int fd_outfile, char **cmd)
{
	char *path;

    if (dup2(fd_infile, STDIN_FILENO) == -1 || dup2(fd_outfile, STDOUT_FILENO) == -1)
    {
        clean_up(pipex);
        error_exit("dup2 failed", 1);
    }
    
    // Close all file descriptors since we've already duplicated what we need
    close(fd_infile);
    close(fd_outfile);
    close(pipex->fd_infile);
    close(pipex->fd_outfile);
    
    if (!cmd || !cmd[0])
    {
        clean_up(pipex);
        error_exit("command not found", 127);
    }
    
    path = get_path(cmd[0], pipex->envp);
    if (!path)
    {
        clean_up(pipex);
        error_exit(cmd[0], 127);
    }
    
    execve(path, cmd, pipex->envp);
    free(path);
    clean_up(pipex);
    error_exit(cmd[0], 1);
}

void execute_pipe(t_pipex *pipex) {
    int cmd_index;
    int in_fd;
    
    // Start with the input file
    in_fd = pipex->fd_infile;
    
    for (cmd_index = 0; cmd_index < pipex->cmd_count; cmd_index++) {
        // Set up output - either a pipe or the final output file
        int out_fd;
        if (cmd_index == pipex->cmd_count - 1)
            out_fd = pipex->fd_outfile;
        else {
            if (pipe(pipex->fd) == -1)
                error_exit("Pipe creation failed", 1);
            out_fd = pipex->fd[1];
        }
        
        // Fork and execute
        pid_t pid = fork();
        if (pid < 0)
            error_exit("Fork failed", 2);
        
        if (cmd_index == pipex->cmd_count - 1)
            pipex->last_pid = pid;
            
        if (pid == 0)
            child_process(pipex, in_fd, out_fd, pipex->cmds[cmd_index]);
            
        // Close used file descriptors in parent
        if (in_fd != pipex->fd_infile)
            close(in_fd);
        if (out_fd != pipex->fd_outfile)
            close(out_fd);
            
        // Set up for the next command
        if (cmd_index < pipex->cmd_count - 1)
            in_fd = pipex->fd[0];
    }
}

int execute_commands(t_pipex *pipex)
{
    int status = 0;
    int last_status = 0;
    
    execute_pipe(pipex);  // Non-recursive version
    
    // Close any remaining file descriptors
    if (pipex->fd_infile >= 0)
        close(pipex->fd_infile);
    if (pipex->fd_outfile >= 0)
        close(pipex->fd_outfile);
    
    // Wait for all child processes
    while (wait(&status) > 0) {
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
    }
    
    return last_status;
}

