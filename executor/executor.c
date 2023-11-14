/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:35:13 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 10:19:55 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_builtin(t_command cmd, t_shell *shell)
{
	if (ft_strncmp(cmd.cmd, "echo", 4) == 0)
		echo(cmd, *shell);
	else if (ft_strncmp(cmd.cmd, "pwd", 3) == 0)
		pwd(*shell);
	else if (ft_strncmp(cmd.cmd, "cd", 3) == 0)
		cd(cmd, shell);
	else if (ft_strncmp(cmd.cmd, "env", 3) == 0)
		print_envp(cmd, *shell);
	else if (ft_strncmp(cmd.cmd, "export", 6) == 0)
		export(cmd, shell);
	else if (ft_strncmp(cmd.cmd, "unset", 5) == 0)
		unset(cmd, shell);
	else if (ft_strncmp(cmd.cmd, "exit", 4) == 0)
		builtin_exit(cmd, shell);
}

static void	exec_simple_cmd(t_command current, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		printf("Error forking\n");
		return ;
	}
	if (pid == 0)
		execute(current, *shell);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
}

void	executor(t_shell *shell)
{
	t_command	current;
	int			i;
	int			j;

	i = 0;
	shell->commands_num = count_commands(*shell->token_head);
	while (i < shell->commands_num)
	{
		current = shell->commands[i];
		if (is_builtin(current.cmd))
			exec_builtin(current, shell);
		else
			exec_simple_cmd(current, shell);
		i++;
	}
}

static char	*get_path(char **args, t_shell shell)
{
	char	*path;

	if (args[0][0] == '.' || args[0][0] == '/')
	{
		if (access(args[0], X_OK) == 0)
			path = args[0];
	}
	else
		path = find_path(args[0], shell);
	return (path);
}

/* Function that take the command and send it to find_path
 before executing it. */
void	execute(t_command cmd, t_shell shell)
{
	char	*path;
	char	**args;
	int		i;
	int		j;

	signal(SIGINT, child_singal);
	args = arg_expansion(&cmd, shell);
	path = get_path(args, shell);
	if (!path)
	{
		printf("Command not found: %s\n", cmd.cmd);
		free_string_array(args);
		free_everything(&shell);
		free_envp(&shell);
		rl_clear_history();
		exit(127);
	}
	if (execve(path, args, shell.envp) == -1)
	{
		free_string_array(args);
		free_everything(&shell);
		free_envp(&shell);
		rl_clear_history();
		exit(127);
	}
}
