/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 14:20:55 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 10:03:58 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	valid_quotes(char *str)
{
	int	d_quote;
	int	s_quote;
	int	i;
	int	j;
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

void	echo(t_command cmd, t_shell shell)
{
	int		i;
	int		n_flag;
	char	**args;

	i = 0;
	n_flag = 0;
	args = arg_expansion(&cmd, shell);
	while (args[++i])
	{
		if (ft_strncmp(args[i], "$?", 2) == 0 && ft_strlen(args[i]) == 2)
			printf("%d", g_status);
		else if (ft_strncmp(args[i], "-n", 2) == 0 && i == 1)
			n_flag = 1;
		else
			printf("%s", args[i]);
		if (i + 1 <= cmd.args_num && (ft_strncmp(args[i], "-n", 2) != 0))
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	free_string_array(args);
	g_status = 0;
}
