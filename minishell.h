/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:07:52 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 16:45:31 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READ_END	0
# define WRITE_END	1
# define PROMPT "minishell$ "
# define EOF_WARNING "warning: here-document delimited by end-of-file\n"
# define COMMAND_NOT_FOUND ": Command not found\n"
# define NOT_VALID ": not a valid identifier\n"

# define _GNU_SOURCE

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
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
	char	**redirs;
	int		args_num;
	int		redir_in;
	int		redir_out;
	int		here_doc;
	int		append;
	int		cmd_index;
	int		*redir_types;
	t_type	type;
}		t_command;

typedef struct s_shell
{
	int			commands_num;
	int			parse_error;
	int			redir_error_index;
	char		**envp;
	char		*cwd;
	t_token		*token_head;
	t_command	*commands;
	int			previous_status;
	int			expand_heredoc;
}		t_shell;

typedef struct s_pipex{
	int		current_in;
	int		current_out;
	pid_t	*pids;
	int		*pipes_w;
	int		*pipes_r;
	int		*heredoc_r;
	int		status;
}	t_pipex;

/* ---- ENV FUNCTIONS ---- */
int		env_exists(char **ev, char *val);

char	*get_env(char *str, t_shell shell);

void	print_envp(t_command cmd, t_shell shell, int fd);
void	set_env(char **ev, t_shell *shell);
void	realloc_env(char **ev, char *new_var, t_shell *shell);

/* ---- PARSER FUNCTIONS ---- */
int		parser(t_shell *shell);
int		create_command(int *i, int *arg, t_token *current, t_shell *shell);
int		create_arg(int *i, int *arg, t_token *current, t_shell *shell);
int		redir_in(int *i, int *arg, t_token **current, t_shell *shell);
int		redir_out(int *i, int *arg, t_token **current, t_shell *shell);
int		here_doc(int *i, int *arg, t_token **current, t_shell *shell);
int		append(int *i, int *arg, t_token **current, t_shell *shell);
int		init_redirections(t_command *cmd, t_token *current);

void	print_commands(t_shell shell);
void	set_type_arrays(int i, int type, t_token *current, t_shell *shell);

/* ---- EXECUTOR FUNCTIONS ---- */
int		is_builtin(char *str);
void	close_pipes(t_pipex *pipex_data, int j, int num_pipes);
int		ft_strcmp(char *str1, char *str2);
char	*get_path(char **args, t_shell shell);
int		free_pipex(t_pipex *pipex_data);
void	wait_for_processes(t_shell *shell, t_pipex pipex_data);
int		get_num_redirections(t_command command);
int		get_index_infile(t_command command);
int		open_heredocs(t_shell *shell, t_pipex *pipex_data);

int		open_redir_files(t_command command, t_pipex *pipex_data, int cmd_idx);
int		handle_open_in(t_command command, int file_idx, int right_idx);
int		handle_open_out(t_command command, int file_idx, int right_idx);
int		handle_open_append(t_command command, int file_idx, int right_idx);

int		close_files(t_pipex *pipex_data, int free_data);
void	exec_child(t_shell *shell, t_pipex *pipex_data, int i);

int		executor(t_shell *shell);
void	echo(t_command cmd, t_shell shell, int fd);
void	pwd(t_shell shell, int fd);
void	cd(t_command cmd, t_shell *shell);
void	export(t_command cmd, t_shell *shell);
void	unset(t_command cmd, t_shell *shell);
void	builtin_exit(t_command cmd, t_shell *shell, t_pipex *pipex);

/* ---- FREEING FUNCTIONS ---- */
void	free_everything(t_shell *shell);
void	free_envp(t_shell *shell);
void	free_tokens(t_token *token);
void	free_string_array(char **str);

/* ---- EXPANSION FUNCTIONS ---- */
int		quote_val(char c, char *quote);

char	*expand2(char *str, t_shell shell);
char	*expand(char *str, int *k, t_shell shell);
char	**arg_expansion(t_command *cmd, t_shell shell);
char	*expansion_util(char *tmp, char *str, int *j, t_shell shell);
char	*expansion_util2(char *tmp, char *str, int *j, t_shell shell);
char	*construct_str(char *code, char *after_code);
char	*expand3(char *str, t_shell shell);
char	*expansion_logic(char *str, int *j, t_shell shell);

void	init_expand_vars(int *i, int *j, char *quote);
void	init_tmps(char **tmp, char **tmp2, char *str, int *j);

/* ---- GENERAL FUNCTIONS ---- */
int		valid_quotes(char *str);
int		count_args(t_token head);
int		count_commands(t_token head);
int		count_redir(t_token head);

char	*find_path(char *cmd, t_shell shell);

void	handle_signal(int signal);
void	child_signal(int signal);
void	handle_here_doc_signal(int signal);

#endif