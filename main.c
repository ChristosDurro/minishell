/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:07:32 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/13 12:15:53 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;

static void	init_shell(char **ev, t_shell *shell, int argc, char **argv)
{
	set_env(ev, shell);
	shell->cwd = getcwd(NULL, 0);
	shell->parse_error = 0;
	shell->previous_status = 0;
	shell->redir_error_index = -1;
	signal(SIGINT, &handle_signal);
	signal(SIGQUIT, SIG_IGN);
	g_status = 0;
	argc = 0;
	argv = NULL;
}

static int	main_functions(char *cmd, t_shell *shell)
{
	add_history(cmd);
	shell->token_head = lexer(cmd);
	if (!shell->token_head)
		return (1);
	if (!parser(shell))
	{
		free(cmd);
		free_everything(shell);
		return (1);
	}
	executor(shell);
	return (0);
}

static int	check_cmd_null(char *cmd, t_shell *shell)
{
	if (cmd == NULL)
	{
		free_envp(shell);
		free(shell->cwd);
		rl_clear_history();
		printf("exit\n");
		exit(g_status);
	}
	while (*cmd && *cmd == ' ')
		cmd++;
	if (*cmd == '\0')
		return (1);
	else if (ft_strncmp(cmd, "\n", 1) == 0)
	{
		free(cmd);
		return (1);
	}
	return (0);
}

static void	terminate_main(t_shell *shell)
{
	free_envp(shell);
	free(shell->cwd);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*cmd;
	char	*tmp;

	init_shell(envp, &shell, argc, argv);
	while (1)
	{
		cmd = readline(PROMPT);
		shell.previous_status = g_status;
		if (check_cmd_null(cmd, &shell))
		{
			tmp = ft_strdup(cmd);
			free(cmd);
			free(tmp);
			continue ;
		}
		g_status = 0;
		if (main_functions(cmd, &shell))
			continue ;
		free(cmd);
		free_everything(&shell);
	}
	terminate_main(&shell);
	return (0);
}
