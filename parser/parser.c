/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:46:12 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 16:54:44 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token head)
{
	t_token	*current;
	int		count;

	current = &head;
	count = 0;
	while (current && current->type != PIPE)
	{
		if (!is_meta(current->value[0])
			&& (current->previous && !is_meta(current->previous->value[0])))
			count++;
		current = current->next;
	}
	return (count);
}

int	count_commands(t_token head)
{
	t_token	*current;
	int		count;

	count = 1;
	current = &head;
	while (current)
	{
		if (ft_strncmp(current->value, "|", 1) == 0)
			count++;
		current = current->next;
	}
	return (count);
}

int	command_struct_len(t_shell shell)
{
	t_command	*current;
	int			len;

	len = 0;
	if (ft_strncmp(shell.commands[0].cmd, "", 1) == 0)
		return (len);
	else
		current = shell.commands;
	while (current[len].cmd)
		len++;
	return (len);
}

static void	parser_logic(int *i, int *arg, t_token **current, t_shell *shell)
{
	if ((*current)->type == WORD
		&& ((*current)->previous == NULL
			|| (*current)->previous->type == PIPE))
		shell->parse_error = create_command(i, arg, (*current), shell);
	else if ((*current)->type == WORD
		&& !is_meta((*current)->previous->value[0])
		&& (*current)->index != shell->commands[(*i)].cmd_index)
		shell->parse_error = create_arg(i, arg, (*current), shell);
	else if ((*current)->type == REDIR_IN)
		shell->parse_error = redir_in(i, arg, current, shell);
	else if ((*current)->type == REDIR_OUT)
		shell->parse_error = redir_out(i, arg, current, shell);
	else if ((*current)->type == HERE_DOC)
		shell->parse_error = here_doc(i, arg, current, shell);
	else if ((*current)->type == APPEND)
		shell->parse_error = append(i, arg, current, shell);
	else if ((*current)->type == PIPE && !(*current)->next)
	{
		printf("No command after pipe\n");
		shell->parse_error = 2;
		shell->redir_error_index = ++(*i);
	}
}

int	parser(t_shell *shell)
{
	int		i;
	int		arg;
	t_token	*current;

	shell->commands_num = count_commands(*shell->token_head);
	shell->commands = malloc(sizeof(t_command) * (shell->commands_num));
	current = shell->token_head;
	i = -1;
	arg = 0;
	while (current)
	{
		parser_logic(&i, &arg, &current, shell);
		if (shell->parse_error)
			return (0);
		current = current->next;
	}
	return (1);
}
