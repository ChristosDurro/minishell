/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:45:09 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/08 12:00:50 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(t_type type, char *cmd, t_token *prev, int index)
{
	t_token *token;

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
	t_token *current = token;
	int i;

	i = 0;
	// printf("hello\n");
	while (current)
	{
		printf("token #%d | type: %d | value: %s | index: %d\n", i++, (int)current->type, current->value, current->index);
		current = current->next;
	}
	// printf("token #%d | type: %d | value: %s", i, (int)current->type, current->value);
}