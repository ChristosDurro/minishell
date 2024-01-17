/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:43:33 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 16:10:55 by cdurro           ###   ########.fr       */
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
	if (init_redirections(&shell->commands[(*i)], current))
		return (1);
	shell->commands[(*i)].cmd_index = (*current).index;
	return (0);
}

int	create_arg(int *i, int *arg, t_token *current, t_shell *shell)
{
	shell->commands[(*i)].args[(*arg)] = current->value;
	(*arg)++;
	return (0);
}

int	count_redir(t_token head)
{
	t_token	*current;
	int		redirs;

	current = &head;
	redirs = 0;
	while (current)
	{
		if (is_meta(current->value[0]) && current->value[0] != '|')
			redirs++;
		current = current->next;
	}
	return (redirs);
}

int	init_redirections(t_command *cmd, t_token *current)
{
	cmd->redir_in = 0;
	cmd->redir_out = 0;
	cmd->here_doc = 0;
	cmd->append = 0;
	cmd->redirs = ft_calloc(sizeof(char *), count_redir((*current)) + 1);
	cmd->redir_types = ft_calloc(sizeof(int), count_redir((*current)) + 1);
	if (!cmd->redirs || !cmd->redir_types)
		return (1);
	return (0);
}

void	set_type_arrays(int i, int type, t_token *current, t_shell *shell)
{
	int	j;

	j = 0;
	while (shell->commands[i].redirs[j])
		j++;
	if (type == REDIR_IN)
		shell->commands[i].redir_in++;
	else if (type == REDIR_OUT)
		shell->commands[i].redir_out++;
	else if (type == HERE_DOC)
		shell->commands[i].here_doc++;
	else if (type == APPEND)
		shell->commands[i].append++;
	shell->commands[i].redirs[j] = current->next->value;
	shell->commands[i].redir_types[j] = type;
}
