/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:45:40 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/14 19:48:51 by cdurro           ###   ########.fr       */
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
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
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
int		get_len(char *cmd);
int		is_operator(char *cmd);

void	print_lexer(t_token *token);

t_token	*lexer(char *cmd);
t_token	*new_token(t_type type, char *cmd, t_token *prev, int index);

#endif