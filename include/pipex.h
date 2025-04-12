

#ifndef PIPEX_H
# define PIPEX_H

# include "../greg_lib/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		fd[2];
	int		fd_infile;
	int		fd_outfile;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
	char	**argv;
	int		argc;
	int		file_error;
}			t_pipex;

/************ ERROR HANDLING ************/
void		error_exit(const char *msg, int exit_code);
void		handle_error(int argc, char **argv);

/************ CLEANING ************/
void		free_tab(char **tab);

/************ PARSING ************/
void		handle_arguments(t_pipex *pipex, int argc, char **argv,
				char **envp);
void		handle_files(t_pipex *pipex);
void		child_process(int fd_infile, int fd_outfile, char **cmd,
				char **envp);
int			execute_commands(t_pipex *pipex);

/************ PATH ************/
char		*get_path(char *cmd, char **envp);

#endif
