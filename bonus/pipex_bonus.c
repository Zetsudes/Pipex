/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:47:20 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/29 15:47:52 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	memset(&pipex, 0, sizeof(t_pipex));
	if (argc < 5)
		error_exit("Usage: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 1, NULL);
	handle_error(argc, argv);
	handle_arguments(&pipex, argc, argv, envp);
	handle_files(&pipex);
	exit_status = execute_commands(&pipex);
	clean_up(&pipex);
	return (exit_status);
}
