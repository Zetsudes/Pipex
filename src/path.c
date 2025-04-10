/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:46:38 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/08 12:35:53 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/pipex.h"

char	*get_path(char *cmd, char **envp)
{
	char	*path;
	char	**dir;
	char	*final_path;
	char	*tmp;
	int i;

	i = 0;
	while(envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return(NULL);
	path = envp[i] + 5;
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		tmp = ft_strjoin(dir[i], "/");
		final_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(final_path, F_OK | X_OK) == 0)
		{
			free_tab(dir);
			return (final_path);
		}
		free(final_path);
		i++;
	}
	free_tab(dir);
	return (NULL);
}
