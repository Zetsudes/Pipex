
#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	handle_error(argc, argv);
	handle_arguments(&pipex, argc, argv, envp);
	handle_files(&pipex);
	exit_status = execute_commands(&pipex);
	free_tab(pipex.cmd1);
	free_tab(pipex.cmd2);
	return (exit_status);
}
