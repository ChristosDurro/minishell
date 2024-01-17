/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:35:13 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/11 16:06:11 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wrapper_piping(int *ends)
{
	if (pipe(ends) < 0)
	{
		g_status = 1;
		perror("piping error");
		return (1);
	}
	return (0);
}

static int	init_pipes_and_pids(t_shell *shell, t_pipex *pipex_data)
{
	int	i;
	int	ends[2];

	pipex_data->pipes_r = malloc(sizeof(int) * (shell->commands_num - 1));
	pipex_data->pipes_w = malloc(sizeof(int) * (shell->commands_num - 1));
	pipex_data->pids = malloc(sizeof(int) * shell->commands_num);
	pipex_data->heredoc_r = malloc(sizeof(int) * shell->commands_num);
	if (!pipex_data->pipes_r || !pipex_data->pipes_w || \
		!pipex_data->pids || !pipex_data->heredoc_r)
	{
		free_pipex(pipex_data);
		return (1);
	}
	i = 0;
	while (i < shell->commands_num - 1)
	{
		pipex_data->pids[i] = -1;
		if (wrapper_piping(ends))
			return (free_pipex(pipex_data));
		pipex_data->pipes_w[i] = ends[1];
		pipex_data->pipes_r[i] = ends[0];
		i++;
	}
	pipex_data->pids[i] = -1;
	return (0);
}

static int	wrapper_forking(t_pipex *pipex_data, pid_t i, t_shell *shell)
{
	if (shell->commands[i].cmd == NULL || \
		(is_builtin(shell->commands[i].cmd) && shell->commands_num == 1))
	{
		pipex_data->pids[i] = -1;
		return (0);
	}
	pipex_data->pids[i] = fork();
	if (pipex_data->pids[i] < 0)
		return (1);
	return (0);
}

static int	executor_loop(t_shell *shell, t_pipex *pipex_data, int i)
{
	if (open_redir_files(shell->commands[i], pipex_data, i))
	{
		close_pipes(pipex_data, i, shell->commands_num - 1);
		g_status = 1;
		return (1);
	}
	if (wrapper_forking(pipex_data, i, shell))
	{
		printf("forking failed\n");
		g_status = 1;
		return (1);
	}
	if (shell->commands[i].cmd && pipex_data->pids[i] <= 0)
		exec_child(shell, pipex_data, i);
	return (0);
}

int	executor(t_shell *shell)
{
	int		i;
	t_pipex	pipex_data;

	signal(SIGINT, &child_signal);
	signal(SIGQUIT, &child_signal);
	if (init_pipes_and_pids(shell, &pipex_data) || \
		open_heredocs(shell, &pipex_data))
		return (1);
	i = 0;
	while (i < shell->commands_num)
		executor_loop(shell, &pipex_data, i++);
	close_pipes(&pipex_data, shell->commands_num, shell->commands_num - 1);
	wait_for_processes(shell, pipex_data);
	free_pipex(&pipex_data);
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}
