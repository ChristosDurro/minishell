/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:04 by thofting          #+#    #+#             */
/*   Updated: 2023/12/15 17:33:16 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_after_exec(t_shell *shell, t_pipex *pipex_data)
{
	free_everything(shell);
	free_envp(shell);
	free(shell->cwd);
	free_pipex(pipex_data);
	rl_clear_history();
}

static void	exec_builtin(t_command cmd, t_shell *shell, \
	t_pipex *pipex_data)
{
	int	fd_out;

	fd_out = STDOUT_FILENO;
	if (shell->commands_num == 1 && pipex_data->current_out >= 0)
		fd_out = pipex_data->current_out;
	if (cmd.cmd == NULL)
		return ;
	else if (ft_strncmp(cmd.cmd, "echo", 4) == 0)
		echo(cmd, *shell, fd_out);
	else if (ft_strncmp(cmd.cmd, "pwd", 3) == 0)
		pwd(*shell, fd_out);
	else if (ft_strncmp(cmd.cmd, "cd", 2) == 0)
		cd(cmd, shell);
	else if (ft_strncmp(cmd.cmd, "env", 3) == 0)
		print_envp(cmd, *shell, fd_out);
	else if (ft_strncmp(cmd.cmd, "export", 6) == 0)
		export(cmd, shell);
	else if (ft_strncmp(cmd.cmd, "unset", 5) == 0)
		unset(cmd, shell);
	else if (ft_strncmp(cmd.cmd, "exit", 4) == 0)
		builtin_exit(cmd, shell, pipex_data);
	if (shell->commands_num == 1)
		return ;
	free_after_exec(shell, pipex_data);
	exit(EXIT_SUCCESS);
}

static void	exec_command(t_command cmd, t_shell *shell, \
	t_pipex *pipex_data)
{
	char	*path;
	char	**args;

	args = arg_expansion(&cmd, *shell);
	path = get_path(args, *shell);
	if (path)
		execve(path, args, shell->envp);
	write(2, cmd.cmd, ft_strlen(cmd.cmd));
	write(2, COMMAND_NOT_FOUND, ft_strlen(COMMAND_NOT_FOUND));
	free_string_array(args);
	free_after_exec(shell, pipex_data);
	exit(EXIT_FAILURE);
}

void	exec_child(t_shell *shell, t_pipex *pipex_data, int i)
{
	t_command	current;

	current = shell->commands[i];
	if (current.cmd == NULL)
		return (close_pipes(pipex_data, i, shell->commands_num - 1));
	if (pipex_data->current_in >= 0 && \
		!(is_builtin(shell->commands[i].cmd) && shell->commands_num == 1))
		dup2(pipex_data->current_in, STDIN_FILENO);
	else if (i > 0)
		dup2(pipex_data->pipes_r[i - 1], STDIN_FILENO);
	if (pipex_data->current_out >= 0 && \
		!(is_builtin(shell->commands[i].cmd) && shell->commands_num == 1))
		dup2(pipex_data->current_out, STDOUT_FILENO);
	else if (i < shell->commands_num - 1)
		dup2(pipex_data->pipes_w[i], STDOUT_FILENO);
	if (is_builtin(current.cmd))
		exec_builtin(current, shell, pipex_data);
	else
	{
		close_pipes(pipex_data, shell->commands_num, shell->commands_num - 1);
		exec_command(current, shell, pipex_data);
	}
}
