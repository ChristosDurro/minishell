/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofting <thofting@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:38 by thofting          #+#    #+#             */
/*   Updated: 2023/11/28 17:14:39 by thofting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	free_pipex(t_pipex *pipex_data)
{
	if (pipex_data->pids)
		free(pipex_data->pids);
	if (pipex_data->pipes_w)
		free(pipex_data->pipes_w);
	if (pipex_data->pipes_r)
		free(pipex_data->pipes_r);
	if (pipex_data->heredoc_r)
		free(pipex_data->heredoc_r);
	return (1);
}

void	close_pipes(t_pipex *pipex_data, int j, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipex_data->pipes_w[i] >= 0 && i <= j)
		{
			close(pipex_data->pipes_w[i]);
			pipex_data->pipes_w[i] = -2;
		}
		if (pipex_data->pipes_r[i] >= 0 && i < j)
		{
			close(pipex_data->pipes_r[i]);
			pipex_data->pipes_r[i] = -2;
		}
		i++;
	}
}

void	wait_for_processes(t_shell *shell, t_pipex pipex_data)
{
	int	i;

	i = 0;
	while (i < shell->commands_num)
	{
		if (pipex_data.pids[i] != -1)
		{
			waitpid(pipex_data.pids[i], &(pipex_data.status), 0);
			if (WIFEXITED(pipex_data.status))
				g_status = WEXITSTATUS(pipex_data.status);
		}
		i++;
	}
}

char	*get_path(char **args, t_shell shell)
{
	char	*path;

	path = NULL;
	if (args[0][0] == '.' || args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
			path = args[0];
	}
	else
		path = find_path(args[0], shell);
	return (path);
}
