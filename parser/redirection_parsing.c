/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:16:53 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 16:41:49 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_command_redir(int *i, int *arg, t_token *current, t_shell *shell)
{
	(*i)++;
	if (init_redirections(&shell->commands[(*i)], current))
		return (1);
	while (current->next->next && (current->next->next->type != WORD
			&& current->next->next->type != PIPE))
		current = current->next->next;
	shell->commands[(*i)].args_num = count_args(*current);
	shell->commands[(*i)].args = ft_calloc(sizeof(char *),
			shell->commands[(*i)].args_num + 1);
	if (!shell->commands[(*i)].args
		&& printf("allocation of args failed.\n"))
		return (1);
	(*arg) = 0;
	if (!current->next->next || current->next->next->type == PIPE)
	{
		shell->commands[(*i)].cmd = NULL;
		shell->commands[(*i)].cmd_index = -1;
	}
	else
	{
		shell->commands[(*i)].cmd = current->next->next->value;
		shell->commands[(*i)].cmd_index = (*current).next->next->index;
	}
	return (0);
}

int	redir_in(int *i, int *arg, t_token **current, t_shell *shell)
{
	int	created;

	created = 0;
	if (((!(*current)->next || (*current)->next->type == PIPE))
		&& printf("Parser Error: invalid < syntax.\n"))
	{
		g_status = 2;
		shell->redir_error_index = ++(*i);
		if (!(*current)->previous || (*current)->previous->type == PIPE)
			return (2);
		else
			return (3);
	}
	if (!(*current)->previous || (*current)->previous->type == PIPE)
	{
		if (create_command_redir(i, arg, (*current), shell))
			return (1);
		created = 1;
	}
	set_type_arrays(*i, REDIR_IN, *current, shell);
	if (!created)
		(*current) = (*current)->next;
	return (0);
}

int	redir_out(int *i, int *arg, t_token **current, t_shell *shell)
{
	int	created;

	created = 0;
	if (((!(*current)->next || (*current)->next->type == PIPE))
		&& printf("Parser Error: invalid > syntax.\n"))
	{
		g_status = 2;
		shell->redir_error_index = ++(*i);
		if (!(*current)->previous || (*current)->previous->type == PIPE)
			return (2);
		else
			return (3);
	}
	if (!(*current)->previous || (*current)->previous->type == PIPE)
	{
		if (create_command_redir(i, arg, (*current), shell))
			return (1);
		created = 1;
	}
	set_type_arrays(*i, REDIR_OUT, *current, shell);
	if (!created)
		(*current) = (*current)->next;
	return (0);
}

int	here_doc(int *i, int *arg, t_token **current, t_shell *shell)
{
	int	created;

	created = 0;
	if (((!(*current)->next || (*current)->next->type == PIPE))
		&& printf("Parser Error: invalid << syntax.\n"))
	{
		g_status = 2;
		shell->redir_error_index = ++(*i);
		if (!(*current)->previous || (*current)->previous->type == PIPE)
			return (2);
		else
			return (3);
	}
	if (!(*current)->previous || (*current)->previous->type == PIPE)
	{
		if (create_command_redir(i, arg, (*current), shell))
			return (1);
		created = 1;
	}
	set_type_arrays(*i, HERE_DOC, *current, shell);
	if (!created)
		(*current) = (*current)->next;
	return (0);
}

int	append(int *i, int *arg, t_token **current, t_shell *shell)
{
	int	created;

	created = 0;
	if (((!(*current)->next || (*current)->next->type == PIPE))
		&& printf("Parser Error: invalid >> syntax.\n"))
	{
		g_status = 2;
		shell->redir_error_index = ++(*i);
		if (!(*current)->previous || (*current)->previous->type == PIPE)
			return (2);
		else
			return (3);
	}
	if (!(*current)->previous || (*current)->previous->type == PIPE)
	{
		if (create_command_redir(i, arg, (*current), shell))
			return (1);
		created = 1;
	}
	set_type_arrays(*i, APPEND, *current, shell);
	if (!created)
		(*current) = (*current)->next;
	return (0);
}
