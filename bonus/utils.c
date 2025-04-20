
#include "../include/pipex_bonus.h"


void    error_exit(const char *msg, int exit_code, void *to_free)
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

void    handle_error(int argc, char **argv)
{
    int is_heredoc;
    
    is_heredoc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
    
    if ((is_heredoc && argc < 6) || (!is_heredoc && argc < 5))
        error_exit("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n       ./pipex here_doc LIMITER cmd1 cmd2 ... cmdn file2", 1, NULL);
    
    if (!is_heredoc && access(argv[1], R_OK) == -1)
        perror(argv[1]);
    
    if (access(argv[argc - 1], W_OK) == -1 && access(argv[argc - 1], F_OK) == 0)
        perror(argv[argc - 1]);
}

void    free_tab(char **tab)
{
    size_t    i;

    i = 0;
    if (!tab)
        return;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

void    clean_up(t_pipex *pipex)
{
    int i;
    
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

void    child_process(t_pipex *pipex, int fd_in, int fd_out, char **cmd)
{
    char *path;
    char *cmd_name;
    
    if (dup2(fd_in, STDIN_FILENO) == -1 || dup2(fd_out, STDOUT_FILENO) == -1)
    {
        close(fd_in);
        close(fd_out);
        clean_up(pipex);
        error_exit("dup2 failed", 1, NULL);
    }
    
    close_pipes(pipex);
    close(fd_in);
    close(fd_out);
    
    if (!cmd || !cmd[0])
    {
        clean_up(pipex);
        error_exit("command not found", 127, NULL);
    }
    
    cmd_name = ft_strdup(cmd[0]);
    if (!cmd_name)
    {
        clean_up(pipex);
        error_exit("Memory allocation failed", 1, NULL);
    }
    
    path = get_path(cmd[0], pipex->envp);
    if (!path)
    {
        clean_up(pipex);
        error_exit(cmd_name, 127, cmd_name);
    }
    
    execve(path, cmd, pipex->envp);
    free(path);
    clean_up(pipex);
    error_exit(cmd_name, 1, cmd_name);
}
