
#include "../include/pipex_bonus.h"

void	error_exit(const char *msg, int exit_code, int **free)
{
	if (free)
		free_tab(free);
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
	if (argc < 5)
		error_exit("Usage: ./pipex infile cmd1 cmd2 outfile", 1, NULL);
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

void	free_cmds(char ***tab)
{
	size_t i;
	size_t j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			free(tab[i][j]);
			j++;
		}
		free(tab[i]);
		i++;
	}
	free(tab);
}
