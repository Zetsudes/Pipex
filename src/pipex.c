
# include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipex pipex;

    handle_error(argc, argv);
    pipex.argc = argc;
    pipex.argv = argv;
    pipex.envp = envp;
    handle_arguments(&pipex);
    handle_files(&pipex);
    execute_commands(&pipex);
    free_tab(pipex.cmd1);
    free_tab(pipex.cmd2);
    return (0);
}