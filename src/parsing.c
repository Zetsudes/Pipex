
# include "../include/pipex.h"

void    handle_arguments(int argc, char **argv, char **cmd1, char **cmd2)
{
    cmd1 = ft_split(argv[2], " ");
    cmd2 = ft_split(argv[3], " ");
}

void    handle_files(int argc, char **argv, int *fd_infile, int *fd_outfile, int fd[2])
{
    if (pipe(fd) == -1)
        error_exit("Pipe creation failed :(", 1);
    fd_infile = open(argv[1], O_RDONLY);
    fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_infile < 0 || fd_outfile < 0)
        error_exit("File error : (", 1);
}

void    execute_commands(int fd[2], int fd_infile, int fd_outfile, char **cmd1, char **cmd2)
{
    int pid1;
    int pid2;

    pid1 = fork();
    if (pid1 < 0)
        error_exit("Oopsie fork failed :(", 2);
    if (pid1 == 0)
    {
        dup2(fd_infile, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        execve(cmd1[0], cmd1, NULL);
        error_exit("Execve failed :(", 1);
    }
    pid2 = fork();
    if (pid2 < 0)
        error_exit("Oopsie fork failed :( ", 2);
    if (pid2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);
        dup2(fd_outfile, STDOUT_FILENO);
        execve(cmd2[0], cmd2, NULL);
        error_exit("Execve failed :(", 1);
    }
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}