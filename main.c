/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:07:32 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/26 17:07:16 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

void	print_env(char **ev)
{
	int i;

	i = 0;
	while (ev[i])
	{
		printf("%s\n", ev[i]);
		i++;
	}
}

int init_shell(char **ev, t_shell *shell)
{
	shell->envp = set_env(ev);
	shell->cwd = getcwd(shell->cwd, 256);
	
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_shell shell;
	t_termios term_backup;
	char *cmd;
	char *tmp;

	init_shell(envp, &shell);
	// ft_bzero(&term_backup, sizeof(term_backup));
	// shell.term_backup = &term_backup;
	// g_shell.cwd = getcwd(g_shell.cwd, 256);
	// print_envp();
	// printf("%s\n", get_env("PWD"));
	while (1)
	{
		// print_env(envp);
		signal(SIGINT, handle_signal);
		signal(SIGQUIT, SIG_IGN);

		// if(setup_term(&term_backup, shell))
		// 	printf("Some error seting up the term!");
		// tmp = getcwd(g_shell.cwd, 256);
		cmd = readline(PROMPT);
		// reset_term(&term_backup);

		if (cmd == NULL)
			exit(1);
		while (*cmd && *cmd == ' ')
			cmd++;
		if (*cmd == '\0')
			continue;
		else if (cmd[0] == '\0' || ft_strncmp(cmd, "\n", 1) == 0)
		{
			free(cmd);
			continue;
		}
		else if (ft_strncmp(cmd, "exit", 5) == 0)
		{
			free(cmd);
			exit(g_status);
		}

		// printf("%s\n", cmd);
		// printf("%s\n", find_path(cmd, envp));
		// execute(cmd, envp);
		shell.token_head = lexer(cmd);
		print_lexer(shell.token_head);
		// parser();

		if (ft_strncmp(cmd, "echo ", 5) == 0)
			echo(shell.token_head, shell);
		else if (ft_strncmp(cmd, "pwd ", 4) == 0)
			pwd(shell);
		else if (ft_strncmp(cmd, "cd ", 3) == 0)
			cd(shell.token_head, &shell);
		else if (ft_strncmp(cmd, "env", 3) == 0)
			print_envp(shell.token_head, shell);
		else if (ft_strncmp(cmd, "export ", 7) == 0)
			export(shell.token_head, &shell);
		else if (ft_strncmp(cmd, "unset ", 6) == 0)
			unset(shell.token_head, &shell);
		else// if (find_path(shell.token_head->value, shell.envp) != NULL)
		{
			int	p[2];
			int pid;
			int	i;
			char **split_commands;
			
			split_commands = ft_split(cmd, '|');
			// if (pipe(p) == -1)
			// {
			// 	printf("error pipeing\n");
			// 	continue;
			// }
			pid = fork();
			if (pid == -1)
			{
				printf("Error forking\n");
				continue;
			}
			if (pid == 0)
			{
				execute(cmd, shell.envp);
			}
			waitpid(pid, NULL, 0);
		}
		add_history(cmd);

		free(cmd);
	}
}