#ifndef PIPEX_H
# define PIPEX_H

# include "../greg_lib/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# define HEREDOC_PROMPT "heredoc> "
# define HEREDOC "here_doc"

typedef struct s_pipex
{
	int     argc;
    char    **argv;
    char    **envp;
    char    ***cmds;
    int     cmd_count;
    int     **pipes;
    int     fd_infile;
    int     fd_outfile;
	int		is_heredoc;
	char    *limiter;
}			t_pipex;

/************ ERROR HANDLING ************/
void        error_exit(const char *msg, int exit_code, void *to_free);
void        handle_error(int argc, char **argv);

/************ CLEANING ************/
void		clean_up(t_pipex *pipex);
void    	free_tab(char **tab);
void        close_pipes(t_pipex *pipex);
void        init_pipes(t_pipex *pipex);

/************ PARSING ************/
void		handle_arguments(t_pipex *pipex, int argc, char **argv, char **envp);
void		handle_files(t_pipex *pipex);
void		child_process(t_pipex *pipex, int fd_infile, int fd_outfile, char **cmd);
int			execute_commands(t_pipex *pipex);
void        handle_heredoc(t_pipex *pipex);
int         create_heredoc_file(char *limiter);

/************ PATH ************/
char		*get_path(char *cmd, char **envp);

#endif
