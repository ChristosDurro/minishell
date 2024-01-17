/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thofting <thofting@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 15:09:48 by thofting          #+#    #+#             */
/*   Updated: 2023/12/10 15:09:50 by thofting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_open_in(t_command command, int file_idx, int right_idx)
{
	int	fd;

	fd = open(command.redirs[file_idx], O_RDONLY);
	if (fd < 0)
	{
		perror(command.redirs[file_idx]);
		return (-1);
	}
	if (file_idx == right_idx)
		return (fd);
	else
		close(fd);
	return (-2);
}

int	handle_open_out(t_command command, int file_idx, int right_idx)
{
	int	fd;

	fd = open(command.redirs[file_idx], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (fd < 0)
	{
		perror(command.redirs[file_idx]);
		return (-1);
	}
	if (file_idx == right_idx)
		return (fd);
	else
		close(fd);
	return (-2);
}

int	handle_open_append(t_command command, int file_idx, int right_idx)
{
	int	fd;

	fd = open(command.redirs[file_idx], O_CREAT | O_APPEND | O_RDWR, 0000644);
	if (fd < 0)
	{
		perror(command.redirs[file_idx]);
		return (-1);
	}
	if (file_idx == right_idx)
		return (fd);
	else
		close(fd);
	return (-2);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	if (!str1 && !str2)
		return (1);
	if ((str1 && !str2) || (!str1 && str2))
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (str1[i] == str2[i]);
}
