/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:14:46 by thofting          #+#    #+#             */
/*   Updated: 2023/12/14 19:47:59 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	close_files(t_pipex *pipex_data, int free_data)
{
	if (pipex_data->current_in >= 0)
		close(pipex_data->current_in);
	if (pipex_data->current_out >= 0)
		close(pipex_data->current_out);
	if (free_data)
		free_pipex(pipex_data);
	return (1);
}

int	get_index_infile(t_command command)
{
	int	num_redir;
	int	i;
	int	right_idx;

	num_redir = command.append + command.here_doc + \
		command.redir_in + command.redir_out;
	i = 0;
	right_idx = -1;
	while (i < num_redir)
	{
		if (command.redir_types[i] == REDIR_IN || \
			command.redir_types[i] == HERE_DOC)
			right_idx = i;
		i++;
	}
	return (right_idx);
}

static int	get_index_outfile(t_command command)
{
	int	num_redir;
	int	i;
	int	right_idx;

	num_redir = command.append + command.here_doc + \
		command.redir_in + command.redir_out;
	i = 0;
	right_idx = -1;
	while (i < num_redir)
	{
		if (command.redir_types[i] == REDIR_OUT || \
			command.redir_types[i] == APPEND)
			right_idx = i;
		i++;
	}
	return (right_idx);
}

int	get_num_redirections(t_command command)
{
	return (command.append + command.here_doc + \
		command.redir_in + command.redir_out);
}

int	open_redir_files(t_command command, t_pipex *pipex_data, int cmd_idx)
{
	int			i;
	int			num_redir;
	int			in_idx;
	int			out_idx;

	pipex_data->current_in = -2;
	pipex_data->current_out = -2;
	num_redir = get_num_redirections(command);
	in_idx = get_index_infile(command);
	out_idx = get_index_outfile(command);
	i = -1;
	while (++i < num_redir)
	{
		if (pipex_data->heredoc_r[cmd_idx] >= 0)
			pipex_data->current_in = pipex_data->heredoc_r[cmd_idx];
		else if (command.redir_types[i] == REDIR_IN)
			pipex_data->current_in = handle_open_in(command, i, in_idx);
		if (command.redir_types[i] == REDIR_OUT)
			pipex_data->current_out = handle_open_out(command, i, out_idx);
		else if (command.redir_types[i] == APPEND)
			pipex_data->current_out = handle_open_append(command, i, out_idx);
		if (pipex_data->current_in == -1 || pipex_data->current_out == -1)
			return (close_files(pipex_data, 0));
	}
	return (0);
}
