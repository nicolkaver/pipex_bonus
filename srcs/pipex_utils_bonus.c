/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:00:19 by nboratko          #+#    #+#             */
/*   Updated: 2022/07/01 14:35:10 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex_bonus.h"

void	cmd_not_found(char **cmd, char *path, t_child *child)
{
	if (path)
		free(path);
	free_split(cmd);
	free(child->pid);
	close(child->outfile);
	close(child->pipefd[0]);
	close(child->pipefd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

static void	empty_cmd(char **argv, char **envp, int i)
{
	char	**cmd;
	char	*check;
	char **path;

	cmd = ft_split(argv[i], ' ');
	path = get_paths_unset(envp);
	if (*argv[i] == '\0')
		ft_putendl_fd("Command '' not found", 2);
	check = find_path(cmd, envp);
	if (path)
	{
	if (!check)
	{
		write(2, cmd[0], ft_strlen(cmd[0]));
		write(2, ": command not found\n", 20);
	}
	}
	free(check);
	free_split(cmd);
}

void	check_args_normal_bonus(char **argv, int argc, char **envp)
{
	int	fd;
	int	i;

	if (argc < 5)
	{
		ft_putendl_fd("Format: ./pipex infile cmd1 ... cmd2 outfile", 2);
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_printf("bash: %s: %s\n", argv[1], strerror(errno));
	if (fd != -1)
		close(fd);
	i = 2;
	if (fd == -1)
		i = 3;
	while (i < argc - 1)
	{
		empty_cmd(argv, envp, i);
		i++;
	}
}

void	check_args_here_doc(char **argv, int argc)
{
	if (argc != 6)
	{
		ft_putendl_fd("Invalid number of arguments for option here_doc", 2);
		exit(EXIT_FAILURE);
	}
	while (argc > 4)
	{
		if (*argv[argc - 2] == '\0')
		{
			ft_putendl_fd("Command '' not found", 2);
		}
		argc--;
	}
}
