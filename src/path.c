/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamohame <zamohame@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 17:46:38 by zamohame          #+#    #+#             */
/*   Updated: 2025/04/28 12:55:38 by zamohame         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// char	*get_path(char *cmd, char **envp)
// {
// 	char	*tmp;
// 	char	*path;
// 	char	*final_path;
// 	char	**dir;
// 	int		i;

// 	i = 0;
// 	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
// 	{
// 		if (access(cmd, F_OK | X_OK) == 0)
// 			return (ft_strdup(cmd));
// 		return (NULL);
// 	}
// 	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
// 		i++;
// 	if (!envp[i])
// 		return (NULL);
// 	path = envp[i] + 5;
// 	dir = ft_split(path, ':');
// 	i = 0;
// 	while (dir[i])
// 	{
// 		tmp = ft_strjoin(dir[i], "/");
// 		final_path = ft_strjoin(tmp, cmd);
// 		free(tmp);
// 		if (access(final_path, F_OK | X_OK) == 0)
// 		{
// 			free_tab(dir);
// 			return (final_path);
// 		}
// 		free(final_path);
// 		i++;
// 	}
// 	free_tab(dir);
// 	return (NULL);
// }

char	*find_path(char **dir, char *cmd)
{
	int		i;
	char	*tmp;
	char	*final_path;

	i = 0;
	while (dir[i])
	{
		tmp = ft_strjoin(dir[i], "/");
		final_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(final_path, F_OK | X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	*path;
	char	**dir;
	char	*final_path;

	i = 0;
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path = env[i] + 5;
	dir = ft_split(path, ':');
	final_path = find_path(dir, cmd);
	free_tab(dir);
	return (final_path);
}
