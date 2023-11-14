/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:45:09 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/10 13:07:23 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(t_type type, char *cmd, t_token *prev, int index)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = cmd;
	token->index = index;
	token->previous = prev;
	token->next = NULL;
	if (prev)
		prev->next = token;
	return (token);
}

int	is_meta(char c)
{
	if (ft_strchr(" \t\n|<>", c))
		return (1);
	return (0);
}

void	print_lexer(t_token *token)
{
	t_token	*current;
	int		i;

	current = token;
	i = 0;
	while (current)
	{
		printf("token #%d | type: %d | value: %s | index: %d\n",
			i++, (int)current->type, current->value, current->index);
		current = current->next;
	}
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->type == WORD)
			free(tmp->value);
		free(tmp);
	}
}
