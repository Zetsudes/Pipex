/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:46:54 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/28 11:46:56 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	pipex;
	int		exit_status;

	handle_error(argc, argv);
	handle_arguments(&pipex, argc, argv, envp);
	handle_files(&pipex);
	exit_status = execute_commands(&pipex);
	clean_up(&pipex);
	return (exit_status);
}
