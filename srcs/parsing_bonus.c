/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:46:01 by nboratko          #+#    #+#             */
/*   Updated: 2022/07/01 14:36:15 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

char	**get_paths_unset(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp && envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	//if (!envp[i])
	//	ft_printf("bash: %s: %s\n", cmd[0], "No such file or directory");
	paths = NULL;
	if (envp[i])
		paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	**get_paths(char **envp, char **cmd)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp && envp[i] && !ft_strnstr(envp[i], "PATH", 4))
		i++;
	if (!envp[i])
		ft_printf("bash: %s: %s\n", cmd[0], "No such file or directory");
	paths = NULL;
	if (envp[i])
		paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*find_path(char **cmd, char **envp)
{
	char	**paths;
	char	*slash;
	char	*path;
	int		i;

	i = 0;
	paths = get_paths(envp, cmd);
	if (!paths)
		return (NULL);
	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
		return (free_split(paths), cmd[0]);
	while (paths[i++])
	{
		slash = ft_strjoin_original(paths[i], "/");
		path = ft_strjoin_original(slash, cmd[0]);
		free(slash);
		if (!path)
			return (free_split(paths), NULL);
		if (access(path, X_OK | F_OK) == 0)
			return (free_split(paths), path);
		free(path);
	}
	free_split(paths);
	return (NULL);
}
