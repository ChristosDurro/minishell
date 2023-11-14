/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:45:40 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/10 11:46:44 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_type		t_type;
typedef struct s_token	t_token;

enum e_type
{
	WORD,
	PIPE,
	COMMAND,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	INVALID,
	APPEND
};

struct s_token
{
	t_type	type;
	char	*value;
	int		index;
	t_token	*next;
	t_token	*previous;
};

int		is_meta(char c);

void	print_lexer(t_token *token);

t_token	*lexer(char *cmd);
t_token	*new_token(t_type type, char *cmd, t_token *prev, int index);

#endif