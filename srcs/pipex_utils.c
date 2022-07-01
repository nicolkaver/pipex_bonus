/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:00:19 by nboratko          #+#    #+#             */
/*   Updated: 2022/06/30 15:37:35 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	free_split(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	cmd_not_found(char **cmd, char *path, t_child *child)
{
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, ": command not found\n", 20);
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

static void	empty_cmd(char **argv, int argc, int fd)
{
	if (*argv[argc - 2] == '\0')
	{
		ft_putendl_fd("Command '' not found", 2);
	}
	if (argc == 5 && fd == -1)
		return ;
}

void	check_args_normal(char **argv, int argc)
{
	int	ret;
	int	fd;

	ret = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_printf("bash: %s: %s\n", argv[1], strerror(errno));
	if (fd != -1)
		close(fd);
	if (argc < 5 || argc > 5)
	{
		ft_putendl_fd("Format: ./pipex infile cmd1 ... cmd2 outfile", 2);
		exit(EXIT_FAILURE);
	}
	while (argc > 3)
	{
		empty_cmd(argv, argc, fd);
		argc--;
	}
}
