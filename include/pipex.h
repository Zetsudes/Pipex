/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:38:12 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/29 15:38:23 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	int		argc;
	char	**argv;
	char	**envp;
	char	**cmd1;
	char	**cmd2;
	int		fd[2];
	int		fd_infile;
	int		fd_outfile;
}			t_pipex;

/************ ERROR HANDLING ************/
void		error_exit(const char *msg, int exit_code, void *to_free);
void		handle_error(int argc, char **argv);
void		fork_error(t_pipex *pipex, pid_t pid, int flag);

/************ CLEANING ************/
void		free_tab(char **tab);
void		clean_up(t_pipex *pipex);

/************ PARSING ************/
void		handle_arguments(t_pipex *pipex, int argc, char **argv,
				char **envp);
void		handle_files(t_pipex *pipex);
void		child_process(t_pipex *pipex, int fd_infile, int fd_outfile,
				char **cmd);
void		child_path(t_pipex *pipex, char **cmd, char *cmd_name);
int			execute_commands(t_pipex *pipex);

/************ PATH ************/
char		*get_path(char *cmd, char **env);
char		*find_path(char **dir, char *cmd);

#endif
