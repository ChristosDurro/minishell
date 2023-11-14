/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:07:07 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:59:06 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Function that will look for the path line inside the environment, will
 split and test each command path and then return the right one. */
char	*find_path(char *cmd, t_shell shell)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	path = get_env("PATH", shell);
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin("/", cmd);
		path = ft_strjoin(paths[i], part_path);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (free(paths), path);
		free(path);
		free(paths[i]);
	}
	free(paths);
	return (0);
}

void	print_envp(t_command cmd, t_shell shell)
{
	int	i;

	if (cmd.args_num)
	{
		printf("%s: No such file or directory\n", cmd.args[0]);
		return ;
	}
	i = 0;
	while (shell.envp[i])
	{
		printf("%s\n", shell.envp[i]);
		i++;
	}
	g_status = 0;
}
