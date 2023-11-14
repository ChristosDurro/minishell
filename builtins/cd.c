/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:22:45 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:58:57 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_command cmd, t_shell *shell)
{
	char	*new_str;
	int		new_len;

	if (ft_strncmp(cmd.args[0], "..", 2) == 0 && ft_strlen(cmd.args[0]) == 2)
	{
		shell->cwd = getcwd(shell->cwd, 256);
		new_str = ft_strrchr(shell->cwd, '/');
		new_len = ft_strlen(shell->cwd) - ft_strlen(new_str);
		new_str = ft_substr(shell->cwd, 0, new_len);
		chdir(new_str);
		free(new_str);
	}
	else if (ft_strncmp(cmd.args[0], ".", 1) == 0
		&& ft_strlen(cmd.args[0]) == 1)
		chdir(shell->cwd);
	else if (ft_strncmp(cmd.args[0], "~", 1) == 0)
	{
		new_str = getenv("HOME");
		chdir(new_str);
	}
	else
		chdir(cmd.args[0]);
	g_status = 0;
}
