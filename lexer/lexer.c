/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:36:24 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/08 14:34:28 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int	is_operator(char *cmd)
{
	if (ft_strncmp(cmd, ">>", 2) == 0
		|| ft_strncmp(cmd, "<<", 2) == 0)
		return (1);
	if (*cmd == '<' || *cmd == '>' || *cmd == '|')
		return (1);
	return (0);
}

static void	handle_operator(char **cmd, t_token **last, int i)
{
	if (ft_strncmp(*cmd, ">>", 2) == 0)
	{
		*last = new_token(APPEND, ">>", *last, i);
		(*cmd) += 2;
	}
	
	else if (ft_strncmp(*cmd, "<<", 2) == 0)
	{
		*last = new_token(HERE_DOC, "<<", *last, i);
		(*cmd) += 2;
	}
	
	else if (**cmd == '|')
	{
		*last = new_token(PIPE, "|", *last, i);
		(*cmd)++;
	}
	
	else if (**cmd == '<')
	{
		*last = new_token(REDIR_IN, "<", *last, i);
		(*cmd)++;
	}
	
	else if (**cmd == '>')
	{
		*last = new_token(REDIR_OUT, ">", *last, i);
		(*cmd)++;
	}

	else if (**cmd == ';')
	{
		*last = new_token(INVALID, ";", *last, i);
		(*cmd)++;
	}
}

static int	get_len(char *cmd, char c)
{
	int		len;
	char	quote;

	len = 0;
	if (cmd[len] == '\'')
	{
		len++;
		while (cmd[len] && cmd[len] != '\'')
			len++;
		return (++len);
	}
	else if (cmd[len] == '"')
	{
		len++;
		while (cmd[len] && cmd[len] != '"')
			len++;
		return (++len);
	}
	else 
	{
		while (cmd[len] && !is_meta(cmd[len]) && (cmd[len] != '"' && cmd[len] != '\''))
			len++;
	}
	return (len);
}

static void	handle_word(char **cmd, t_token **last, int i)
{
	int	len;

	len = get_len(*cmd, '\0');
	*last = new_token(WORD, ft_substr(*cmd, 0, len), *last, i);
	(*cmd) += len;
}

t_token	*lexer(char *cmd)
{
	t_token *start;
	t_token *last;
	int		i;

	start = NULL;
	last = NULL;
	i = 0;
	while (*cmd)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		if (*cmd == '\0')
			break;
		if (is_operator(cmd))
			handle_operator(&cmd, &last, i);
		else
			handle_word(&cmd, &last, i);
		// printf("cmd lexer: %s\n", &cmd);
		if (!start && last)
			start = last;
		i++;
	}
	return (start);
}