
# include "../include/pipex.h"

void    error_exit(const char *msg, int exit_code)
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

void    handle_error(int argc, char **argv)
{
    if (argc != 5)
        error_exit("Invalid number of arguments :(", 1);
    if (access(argv[1], R_OK) == -1)
        error_exit("Infile not accessible in reading mode :(", 126);
    if (access(argv[4], W_OK) == -1 && access(argv[4], F_OK) == -1)
        error_exit("Outfile not accessible in writing mode :(", 126);
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
