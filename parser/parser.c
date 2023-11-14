/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 14:46:12 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/10 13:11:05 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_token head)
{
	t_token	*current;
	int		count;

	current = head.next;
	count = 0;
	while (current && !is_meta(current->value[0]))
	{
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
	if (!head.value)
		return (0);
	else if (head.next)
		current = head.next;
	else
		return (count);
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

int	parser(t_shell *shell)
{
	int		i;
	int		arg;
	t_token	*current;

	shell->commands_num = count_commands(*shell->token_head);
	shell->commands = malloc(sizeof(t_command) * shell->commands_num);
	current = shell->token_head;
	i = -1;
	arg = 0;
	while (current)
	{
		if (current->type == WORD
			&& (current->previous == NULL
				|| ft_strncmp(current->previous->value, "|", 1) == 0))
			shell->parse_error = create_command(&i, &arg, current, shell);
		else if (current->type == WORD)
			shell->parse_error = create_arg(&i, &arg, current, shell);
		else if (current->type == REDIR_IN)
			shell->parse_error = redir_in(&i, current, shell);
		else if (current->type == REDIR_OUT)
			shell->parse_error = redir_out(&i, current, shell);
		current = current->next;
	}
	return (1);
}

void	print_commands(t_shell shell)
{
	int	i;
	int	j;

	i = 0;
	shell.commands_num = count_commands(*shell.token_head);
	while (i < shell.commands_num)
	{
		printf("\n\n");
		printf("command: %s\n", shell.commands[i].cmd);
		j = 0;
		while (shell.commands[i].args[j])
		{
			printf("arg: %s\n", shell.commands[i].args[j]);
			j++;
		}
		printf("redir_in: %d\n", shell.commands[i].redir_in);
		printf("redir_out: %d\n", shell.commands[i].redir_out);
		printf("redir_file: %s\n", shell.commands[i].redir_file);
		i++;
	}
}
