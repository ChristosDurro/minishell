/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 09:36:24 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:11:58 by cdurro           ###   ########.fr       */
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
	if (ft_strncmp(*cmd, ">>", 2) == 0 && (*cmd)++ && (*cmd)++)
		*last = new_token(APPEND, ">>", *last, i);
	else if (ft_strncmp(*cmd, "<<", 2) == 0 && (*cmd)++ && (*cmd)++)
		*last = new_token(HERE_DOC, "<<", *last, i);
	else if (**cmd == '|' && (*cmd)++)
		*last = new_token(PIPE, "|", *last, i);
	else if (**cmd == '<' && (*cmd)++)
		*last = new_token(REDIR_IN, "<", *last, i);
	else if (**cmd == '>' && (*cmd)++)
		*last = new_token(REDIR_OUT, ">", *last, i);
	else if (**cmd == ';' && (*cmd)++)
		*last = new_token(INVALID, ";", *last, i);
}

static int	get_len(char *cmd)
{
	int		len;

	len = 0;
	if (cmd[len] == '\'')
	{
		while (cmd[++len] && !(cmd[len] == '\''
				&& (cmd[len + 1] == ' ' || !cmd[len + 1])))
			;
		return (++len);
	}
	else if (cmd[len] == '"')
	{
		while (cmd[++len] && !(cmd[len] == '"'
				&& (cmd[len + 1] == ' ' || !cmd[len + 1])))
			;
		return (++len);
	}
	else 
	{
		while (cmd[len] && !is_meta(cmd[len]))
			len++;
	}
	return (len);
}

static void	handle_word(char **cmd, t_token **last, int i)
{
	int	len;

	len = get_len(*cmd);
	if (len == 0)
		exit(g_status);
	*last = new_token(WORD, ft_substr(*cmd, 0, len), *last, i);
	(*cmd) += len;
}

t_token	*lexer(char *cmd)
{
	t_token	*start;
	t_token	*last;
	int		i;

	start = NULL;
	last = NULL;
	i = 0;
	if (!valid_quotes(cmd) && printf("Parser Error: unmatched quotes.\n"))
		return (start);
	while (*cmd)
	{
		while (*cmd == ' ' || *cmd == '\t')
			cmd++;
		if (*cmd == '\0')
			break ;
		if (is_operator(cmd))
			handle_operator(&cmd, &last, i);
		else
			handle_word(&cmd, &last, i);
		if (!start && last)
			start = last;
		i++;
	}
	return (start);
}
