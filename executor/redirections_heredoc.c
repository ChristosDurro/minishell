/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:15:01 by thofting          #+#    #+#             */
/*   Updated: 2024/01/13 12:31:43 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_heredoc_pipe(char *temp, int write_end, \
	t_shell shell)
{
	char	*temp_expanded;

	if (shell.expand_heredoc)
		temp_expanded = expand3(temp, shell);
	else
		temp_expanded = ft_strdup(temp);
	write(write_end, temp_expanded, ft_strlen(temp_expanded));
	if (g_status == 0)
		write(write_end, "\n", 1);
	free(temp_expanded);
}

static int	helper_loop(char *delim, int write_end, \
				int write_doc, t_shell *shell)
{
	char	*temp;

	temp = readline("> ");
	if (ft_strcmp(temp, delim) || !temp)
	{
		if (temp)
			free(temp);
		else
			write(2, EOF_WARNING, ft_strlen(EOF_WARNING));
		return (1);
	}
	if (write_doc == 0)
		write_heredoc_pipe(temp, write_end, *shell);
	if (temp)
		free(temp);
	return (0);
}

static int	init_heredoc(t_shell *shell, int file_idx, \
	char **delim, t_command command)
{
	shell->expand_heredoc = 1;
	if (command.redirs[file_idx][0] == '\'' || \
		command.redirs[file_idx][0] == '\"')
		shell->expand_heredoc = 0;
	*delim = ft_strtrim(ft_strdup(command.redirs[file_idx]), "\'\"");
	if (!(*delim))
		return (-1);
	signal(SIGINT, &handle_here_doc_signal);
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

static int	handle_heredoc(t_command command, int file_idx,
				int right_idx, t_shell *shell)
{
	int		ends[2];
	char	*delim;

	if (file_idx == right_idx && pipe(ends) < 0)
	{
		g_status = 1;
		perror("heredoc pipe");
		return (-1);
	}
	delim = NULL;
	if (init_heredoc(shell, file_idx, &delim, command) == -1)
		return (-1);
	while (g_status != 130)
	{
		if (helper_loop(delim, ends[1],
				file_idx - right_idx, shell))
			break ;
	}
	free(delim);
	if (file_idx == right_idx)
	{
		close(ends[1]);
		return (ends[0]);
	}
	return (-2);
}

int	open_heredocs(t_shell *shell, t_pipex *pipex_data)
{
	int			i;
	int			j;
	int			in_idx;
	t_command	command;

	i = -1;
	while (++i < shell->commands_num)
	{
		j = -1;
		command = shell->commands[i];
		in_idx = get_index_infile(command);
		pipex_data->heredoc_r[i] = -2;
		while (++j < get_num_redirections(command))
		{
			if (command.redir_types[j] == HERE_DOC)
			{
				pipex_data->heredoc_r[i] = \
					handle_heredoc(command, j, in_idx, shell);
				if (pipex_data->heredoc_r[i] == -1 || g_status == 130)
					return (free_pipex(pipex_data));
			}
		}
	}
	return (0);
}
