/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:07:07 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/09 14:47:05 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Print a generic error an exits the program with 1. */
void	error(void)
{
	perror("\033[31mError: ");
	exit(EXIT_FAILURE);
}

/* Function that opens the files with the right flags */
int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (cmd[0] == '/')
		paths = ft_split(envp[i] + 5, '/');
	else
		paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		// printf("paths[%d]: %s\n", i, paths[i]);
		if (cmd[0] != '/')
		{
			part_path = ft_strjoin(paths[i], "/");
			// printf("part_path: %s\n", part_path);
			path = ft_strjoin(part_path, cmd);		
			free(part_path);
		}
		else
		{
			part_path = ft_strjoin("/", paths[i]);
			path = ft_strjoin(part_path, cmd);
			free(part_path);
		}
		// printf("path: %s\n\n", path);
		if (access(path, F_OK) == 0)
			return (path);
		i++;
	}
	return (0);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(char *argv, char **envp)
{
	char	**cmd;

	// printf("command received: %s\n", argv);
	cmd = ft_split(argv, ' ');
	if (execve(find_path(cmd[0], envp), cmd, envp) == -1)
	{
		printf("Command not found: %s\n", cmd[0]);
		g_status = 127;
	}
}