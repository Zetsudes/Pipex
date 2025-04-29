/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:39:15 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/29 15:50:00 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

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
	int		argc;
	char	**argv;
	char	**envp;
	char	***cmds;
	int		cmd_count;
	int		**pipes;
	int		fd_infile;
	int		fd_outfile;
	int		is_heredoc;
	char	*limiter;
}			t_pipex;

typedef struct s_exec
{
	int		i;
	pid_t	last_pid;
	int		status;
	int		temp_status;
	pid_t	waited_pid;
	int		fd_in;
}			t_exec;

/************ ERROR HANDLING ************/
void		error_exit(const char *msg, int exit_code, void *to_free);
void		handle_error(int argc, char **argv);

/************ CLEANING ************/
void		clean_up(t_pipex *pipex);
void		free_tab(char **tab);
void		close_pipes(t_pipex *pipex);
void		init_pipes(t_pipex *pipex);
void		fail_dup2(t_pipex *pipex, int fd_in, int fd_out);

/************ PARSING ************/
void		handle_arguments(t_pipex *pipex, int argc, char **argv,
				char **envp);
void		split_arg(t_pipex *pipex, int start_cmd, char **argv);
void		handle_files(t_pipex *pipex);
void		child_process(t_pipex *pipex, int fd_infile, int fd_outfile,
				char **cmd);
int			execute_commands(t_pipex *pipex);
void		handle_child_process(t_pipex *pipex, t_exec *exec, int i);
void		handle_heredoc(t_pipex *pipex);
int			create_heredoc_file(char *limiter);

/************ PATH ************/
char		*get_path(char *cmd, char **envp);
char		*find_path(char **dir, char *cmd);

#endif
