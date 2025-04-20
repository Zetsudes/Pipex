
#include "../include/pipex_bonus.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;
    int     exit_status;

    handle_error(argc, argv);
    handle_arguments(&pipex, argc, argv, envp);
    handle_files(&pipex);
    exit_status = execute_commands(&pipex);
    clean_up(&pipex);
    close(pipex.fd_infile);
    close(pipex.fd_outfile);
    return (exit_status);
}
