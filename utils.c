/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:07:07 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/10 13:10:13 by cdurro           ###   ########.fr       */
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

void	print_envp(t_command cmd, t_shell shell, int fd)
{
	int		i;
	char	*temp;

	if (cmd.args_num)
	{
		ft_putstr_fd(strerror(ENOENT), STDERR_FILENO);
		perror(cmd.args[0]);
		return ;
	}
	i = 0;
	while (shell.envp[i])
	{
		temp = ft_strjoin(shell.envp[i], "\n");
		ft_putstr_fd(temp, fd);
		free(temp);
		i++;
	}
	g_status = 0;
}
/*
static void	print_arr(char *type, char **arr)
{
	int	j;

	printf("\n");
	j = 0;
	while (arr[j])
	{
		printf("%s: %s\n", type, arr[j]);
		j++;
	}
}

void	print_commands(t_shell shell)
{
	int		i;
	int		j;
	char	*type;

	i = 0;
	shell.commands_num = count_commands(*shell.token_head);
	while (i < shell.commands_num)
	{
		printf("\n\ncommand: %s\n", shell.commands[i].cmd);
		print_arr("args", shell.commands[i].args);
		printf("\nredir_in: %d\n", shell.commands[i].redir_in);
		printf("redir_out: %d\n", shell.commands[i].redir_out);
		printf("here_doc: %d\n", shell.commands[i].here_doc);
		printf("append: %d\n", shell.commands[i].append);
		printf("cmd_index: %d\n\n", shell.commands[i].cmd_index);
		j = 0;
		while (shell.commands[i].redir_types[j])
		{
			if (shell.commands[i].redir_types[j] == 3)
				type = "REDIR_IN";
			else if (shell.commands[i].redir_types[j] == 4)
				type = "REDIR_OUT";
			else if (shell.commands[i].redir_types[j] == 5)
				type = "HERE_DOC";
			else
				type = "APPEND";
			printf("redir file: %-10s| redir type: %s\n", \
				shell.commands[i].redirs[j], type);
			j++;
		}
		printf("\n");
		i++;
	}
}
*/
