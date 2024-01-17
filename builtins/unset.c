/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:21:54 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/10 13:15:47 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_var(char *var, t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!env_exists(shell->envp, var))
		return ;
	i = 0;
	while (shell->envp[i] && shell->envp[j])
	{
		if (ft_strncmp(shell->envp[j], var, ft_strlen(var)) == 0
			&& shell->envp[j][ft_strlen(var)] == '=')
		{
			free(shell->envp[i]);
			j++;
		}
		else
		{
			shell->envp[i] = shell->envp[j];
			i++;
			j++;
		}
	}
	shell->envp[i] = 0;
}

void	unset(t_command cmd, t_shell *shell)
{
	char	**args;
	int		i;
	int		j;

	args = arg_expansion(&cmd, *shell);
	i = 1;
	while (args[i])
	{
		j = 0;
		while (shell->envp[j])
			j++;
		unset_var(args[i], shell);
		i++;
	}
	free_string_array(args);
	g_status = 0;
}
