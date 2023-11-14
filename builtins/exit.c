/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:09:07 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:50:44 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_digits(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
		{
			if (!ft_isdigit(args[i][j]))
				return (0);
		}
	}
	return (1);
}

void	builtin_exit(t_command cmd, t_shell *shell)
{
	char	**args;

	printf("num: %d\n", cmd.args_num);
	if (cmd.args_num > 1)
	{
		printf("%s: too many arguments\n", cmd.cmd);
		g_status = 1;
		return ;
	}
	args = arg_expansion(&cmd, *shell);
	if (!check_digits(args))
	{
		printf("%s: non numeric value given\n", cmd.cmd);
		g_status = 2;
	}
	else if (args[1])
		g_status = ft_atoi(args[1]);
	free_everything(shell);
	free_envp(shell);
	free_string_array(args);
	exit(g_status);
}
