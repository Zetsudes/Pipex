
# include "../include/pipex.h"

void    handle_arguments(int argc, char **argv)
{
    char **cmd1;
    char **cmd2;

    cmd1 = ft_split(argv[2], " ");
    cmd2 = ft_split(argv[4], " ");
}

void    handle_files()
{
    int fd_infile;
    int fd_outfile;

    fd_infile = open(argv[1], O_RDONLY);
    fd_outfile = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_infile < 0 || fd_outfile < 0)
        error_exit("File error", 1);
}