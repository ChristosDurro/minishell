/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:07:52 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/09 15:28:30 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


# define READ_END	0
# define WRITE_END	1
# define PROMPT "\033[41mminishell\033[0m$ "

# define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <term.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#include "libft/libft.h"
#include "lexer/lexer.h"

typedef struct termios t_termios;
extern int g_status;

typedef struct s_command
{
	char **cmd_name;
	t_type type;
	struct s_command *next; 
	struct s_command *previous; 
}		t_command;

typedef struct s_shell
{
	char **envp;
	char *cwd;
	t_token *token_head;
	t_command	*commands;
	// t_termios	*term_backup;
	
}		t_shell;

int	open_file(char *argv, int i);
int	env_exists(char **ev, char *val);
int	setup_term(t_termios *term_back, t_shell shell);

char	*find_path(char *cmd, char **envp);
char	**set_env(char **ev);
char	*get_env(char *str, t_shell shell);

void	execute(char *argv, char **envp);
void	handle_signal(int signal);
void	realloc_env(char **ev, char *new_var, int space, t_shell *shell);
void	print_envp(t_token *start, t_shell shell);
void	echo(t_token *start, t_shell shell);
void	pwd(t_shell shell);
void	cd(t_token *start, t_shell *shell);
void	export(t_token *start, t_shell *shell);
void	unset(t_token *start, t_shell *shell);

void	reset_term(t_termios *term_backup);

#endif