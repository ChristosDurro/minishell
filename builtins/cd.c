/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:22:45 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 10:46:09 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	go_back(t_shell *shell)
{
	char	*new_str;
	int		new_len;

	new_str = ft_strrchr(shell->cwd, '/');
	new_len = ft_strlen(shell->cwd) - ft_strlen(new_str);
	new_str = ft_substr(shell->cwd, 0, new_len);
	chdir(new_str);
	free(new_str);
}

static void	change_folder(char *str)
{
	if (chdir(str) == -1)
	{
		perror(str);
		g_status = 1;
	}
}

static void	empty_cd(t_shell *shell)
{
	if (get_env("HOME", *shell) == NULL)
	{
		g_status = 1;
		write(2, "cd: HOME not set\n", ft_strlen("cd: HOME not set\n"));
	}
	else
		chdir(get_env("HOME", *shell));
}

void	cd(t_command cmd, t_shell *shell)
{
	char	**args;

	if (cmd.args_num > 1 && printf("%s: too many arguments\n", cmd.cmd))
	{
		g_status = 1;
		return ;
	}
	args = arg_expansion(&cmd, *shell);
	if (args[1] && ft_strncmp(args[1], "..", 2) == 0 && ft_strlen(args[1]) == 2)
		go_back(shell);
	else if (args[1] && ft_strncmp(args[1], ".", 1) == 0
		&& ft_strlen(args[1]) == 1)
		chdir(shell->cwd);
	else if (args[1] && ft_strncmp(args[1], "~", 1) == 0)
		chdir(get_env("HOME", *shell));
	else if (args[1])
		change_folder(args[1]);
	else
		empty_cd(shell);
	free(shell->cwd);
	shell->cwd = getcwd(NULL, 0);
	if (g_status != 1)
		g_status = 0;
	free_string_array(args);
}
