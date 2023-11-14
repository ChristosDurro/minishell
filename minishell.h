/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:07:52 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 10:19:21 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END	0
# define WRITE_END	1
# define PROMPT "minishell$ "//"\001\033[41mminishell\033[0m\002$ " 

# define _GNU_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# include "libft/libft.h"
# include "lexer/lexer.h"

extern int	g_status;

typedef struct s_command
{
	char	*cmd;
	char	**args;
	char	*redir_file;
	int		args_num;
	int		redir_in;
	int		redir_out;
	t_type	type;
}		t_command;

typedef struct s_shell
{
	int			commands_num;
	int			parse_error;
	char		**envp;
	char		*cwd;
	t_token		*token_head;
	t_command	*commands;
}		t_shell;

/* ---- ENV FUNCTIONS ---- */
int		env_exists(char **ev, char *val);

char	*get_env(char *str, t_shell shell);

void	print_envp(t_command cmd, t_shell shell);
void	set_env(char **ev, t_shell *shell);
void	realloc_env(char **ev, char *new_var, int space, t_shell *shell);

/* ---- PARSER FUNCTIONS ---- */
int		parser(t_shell *shell);
int		create_command(int *i, int *arg, t_token *current, t_shell *shell);
int		create_arg(int *i, int *arg, t_token *current, t_shell *shell);
int		redir_in(int *i, t_token *current, t_shell *shell);
int		redir_out(int *i, t_token *current, t_shell *shell);

void	print_commands(t_shell shell);

/* ---- EXECUTOR FUNCTIONS ---- */
int		is_builtin(char *str);

void	execute(t_command cmd, t_shell shell);
void	executor(t_shell *shell);
void	echo(t_command cmd, t_shell shell);
void	pwd(t_shell shell);
void	cd(t_command cmd, t_shell *shell);
void	export(t_command cmd, t_shell *shell);
void	unset(t_command cmd, t_shell *shell);
void	builtin_exit(t_command cmd, t_shell *shell);

/* ---- FREEING FUNCTIONS ---- */
void	free_everything(t_shell *shell);
void	free_envp(t_shell *shell);
void	free_tokens(t_token *token);
void	free_string_array(char **str);

/* ---- EXPANSION FUNCTIONS ---- */
char	*expand2(char *str, t_shell shell);
char	*expand(char *str, int *k, t_shell shell);
char	**arg_expansion(t_command *cmd, t_shell shell);

/* ---- GENERAL FUNCTIONS ---- */
int		valid_quotes(char *str);
int		count_args(t_token head);
int		count_commands(t_token head);

char	*find_path(char *cmd, t_shell shell);

void	handle_signal(int signal);
void	child_singal(int signal);

#endif