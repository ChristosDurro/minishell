/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:07:32 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/13 11:36:40 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	init_shell(char **ev, t_shell *shell)
{
	char	tmp[1024];

	getcwd(tmp, 1024);
	set_env(ev, shell);
	shell->cwd = tmp;
	shell->parse_error = 0;
	return (1);
}

static int	main_functions(char *cmd, t_shell *shell)
{
	shell->token_head = lexer(cmd);
	if (!shell->token_head)
		return (1);
	print_lexer(shell->token_head);
	add_history(cmd);
	if (!parser(shell))
	{
		free(cmd);
		free_everything(shell);
		return (1);
	}
	if (count_commands(*shell->token_head))
		print_commands(*shell);
	executor(shell);
	return (0);
}

static int	check_cmd_null(char *cmd)
{
	if (cmd == NULL)
		exit(1);
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

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*cmd;
	char	*tmp;

	init_shell(envp, &shell);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		cmd = readline(PROMPT);
		if (check_cmd_null(cmd))
		{
			tmp = ft_strdup(cmd);
			free(cmd);
			free(tmp);
			continue ;
		}
		if (main_functions(cmd, &shell))
			continue ;
		free(cmd);
		free_everything(&shell);
	}
	free_envp(&shell);
	rl_clear_history();
	return (0);
}
