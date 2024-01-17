/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:20:55 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 17:29:05 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_quotes(char *str)
{
	int	d_quote;
	int	s_quote;
	int	i;
	int	len;

	i = 0;
	d_quote = 0;
	s_quote = 0;
	len = ft_strlen(str) - 1;
	while (str[i])
	{
		if (str[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		if (str[i] == '"' && s_quote % 2 == 0)
			d_quote++;
		i++;
	}
	if ((s_quote % 2) || (d_quote % 2))
		return (0);
	return (1);
}

static int	check_n_flag(int i, int j, char *str)
{
	if (ft_strncmp(str, "-n", 2) == 0
		&& ft_strlen(str) == 2 && i == j)
		return (1);
	else if ((ft_strncmp(str, "-n", 2) == 0)
		&& ft_strlen(str) == 2 && i == j - 1)
		return (1);
	return (0);
}

void	echo(t_command cmd, t_shell shell, int fd)
{
	int		i;
	int		j;
	int		n_flag;
	char	**args;

	i = 0;
	j = 1;
	n_flag = 0;
	args = arg_expansion(&cmd, shell);
	while (args[++i])
	{
		if (check_n_flag(i, j, args[i]))
		{
			n_flag = 1;
			j++;
		}
		else
			ft_putstr_fd(args[i], fd);
		if (i + 1 <= cmd.args_num && !(check_n_flag(i, j, args[i])))
			write(fd, " ", 1);
	}
	if (!n_flag)
		write(fd, "\n", 1);
	free_string_array(args);
	g_status = 0;
}
