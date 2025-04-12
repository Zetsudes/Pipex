
#include "../include/pipex.h"

void	error_exit(const char *msg, int exit_code)
{
	if (errno)
		perror(msg);
	else
	{
		ft_putstr_fd((char *)msg, 2);
		ft_putstr_fd("\n", 2);
	}
	exit(exit_code);
}

void	handle_error(int argc, char **argv)
{
	if (argc != 5)
		error_exit("Usage: ./pipex infile cmd1 cmd2 outfile", 1);
	if (access(argv[1], R_OK) == -1)
		perror(argv[1]);
	if (access(argv[4], W_OK) == -1 && access(argv[4], F_OK) == 0)
		perror(argv[4]);
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void	free_all(t_pipex *pipex)
{
	if (pipex->cmd1)
		free_tab(pipex->cmd1);
	if (pipex->cmd2)
		free_tab(pipex->cmd2);
	if (pipex->fd_infile > 0)
		close(pipex->fd_infile);
	if (pipex->fd_outfile > 0)
		close(pipex->fd_outfile);
	if (pipex->fd[0] > 0)
		close(pipex->fd[0]);
	if (pipex->fd[1] > 0)
		close(pipex->fd[1]);
}
