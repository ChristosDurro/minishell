/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:19:39 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/28 13:23:07 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	extend(char *cmd, char c)
{
	int	i;

	i = 0;
	while (cmd[++i] && cmd[i] != c)
		;
	return (++i);
}

int	get_len(char *cmd)
{
	int	len;

	len = -1;
	while (cmd[++len] && !is_meta(cmd[len]))
	{
		if (cmd[len] == '"' || cmd[len] == '\'')
			len += extend(&cmd[len], cmd[len]) - 1;
	}
	return (len);
}

int	is_operator(char *cmd)
{
	if (ft_strncmp(cmd, ">>", 2) == 0
		|| ft_strncmp(cmd, "<<", 2) == 0)
		return (1);
	if (*cmd == '<' || *cmd == '>' || *cmd == '|')
		return (1);
	return (0);
}
