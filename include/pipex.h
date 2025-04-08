

#ifndef PIPEX_H
# define PIPEX_H

# include "../greg_lib/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include<sys/types.h>
# include<sys/stat.h>

/************ ERROR HANDLING ************/
void    error_exit(const char *msg, int exit_code);
void    handle_error(int argc, char **argv);

/************ CLEANING ************/
void	free_tab(char **tab);

/************ PARSING ************/
void    handle_arguments(int argc, char **argv, char ***cmd1, char ***cmd2);
void    handle_files(int argc, char **argv, int *fd_infile, int *fd_outfile, int fd[2]);
void	child_process(int fd_infile, int fd_outfile, char **cmd, char **envp);
void    execute_commands(int fd[2], int fd_infile, int fd_outfile, char **cmd1, char **cmd2);

/************ PATH ************/
char	*get_path(char *cmd, char **envp);

#endif
