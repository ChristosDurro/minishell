/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:43:33 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:14:19 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_command(int *i, int *arg, t_token *current, t_shell *shell)
{
	(*i)++;
	shell->commands[(*i)].args_num = count_args(*current);
	shell->commands[(*i)].args = ft_calloc(sizeof(char *),
			shell->commands[(*i)].args_num + 1);
	if (!shell->commands[(*i)].args)
	{
		printf("allocation of args failed.\n");
		return (1);
	}
	(*arg) = 0;
	shell->commands[(*i)].cmd = current->value;
	shell->commands[(*i)].redir_in = 0;
	shell->commands[(*i)].redir_out = 0;
	shell->commands[(*i)].redir_file = NULL;
	return (0);
}

int	create_arg(int *i, int *arg, t_token *current, t_shell *shell)
{
	shell->commands[(*i)].args[(*arg)] = current->value;
	(*arg)++;
	return (0);
}

int	redir_in(int *i, t_token *current, t_shell *shell)
{
	if ((!current->next || !current->previous || i < 0)
		&& printf("Parser Error: invalid < syntax.\n"))
		return (1);
	shell->commands[(*i)].redir_in = 1;
	shell->commands[(*i)].redir_file = current->next->value;
	current = current->next;
	return (0);
}

int	redir_out(int *i, t_token *current, t_shell *shell)
{
	if ((!current->next || !current->previous || i < 0)
		&& printf("Parser Error: invalid > syntax.\n"))
		return (1);
	shell->commands[(*i)].redir_out = 1;
	shell->commands[(*i)].redir_file = current->next->value;
	current = current->next;
	return (0);
}
