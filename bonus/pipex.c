
#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	handle_error(argc, argv);
	handle_arguments(&pipex, argc, argv, envp);
	handle_pipes(&pipex);
	exit_status = execute_commands(&pipex);
	free_cmds(pipex.cmds);
	return (exit_status);
}
