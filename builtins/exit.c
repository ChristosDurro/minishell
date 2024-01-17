/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 10:09:07 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/14 20:12:08 by cdurro           ###   ########.fr       */
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

static void	free_stuff(char **args, t_pipex *pipex, t_shell *shell)
{
	free_everything(shell);
	free_envp(shell);
	free(shell->cwd);
	free_string_array(args);
	free_pipex(pipex);
}

static void	set_status(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": numeric argument required\n", \
		ft_strlen(": numeric argument required\n"));
	g_status = 2;
}

static int	check_rest(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

void	builtin_exit(t_command cmd, t_shell *shell, t_pipex *pipex)
{
	char	**args;

	args = arg_expansion(&cmd, *shell);
	if (cmd.args_num > 1)
	{
		write(2, args[0], ft_strlen(args[0]));
		write(2, ": too many arguments\n", ft_strlen(": too many arguments\n"));
		g_status = 1;
		return ;
	}
	if (!check_digits(args))
	{
		if ((args[1][0] == '-' || args[1][0] == '+') && \
			!check_rest(args[1] + 1))
			g_status = ft_atoi(args[1]);
		else
			set_status(args[0]);
	}
	else if (args[1])
		g_status = ft_atoi(args[1]);
	if (shell->commands_num == 1)
		printf("exit\n");
	free_stuff(args, pipex, shell);
	exit(g_status);
}
