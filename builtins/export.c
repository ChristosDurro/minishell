/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:39:27 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:59:38 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_command cmd, t_shell *shell)
{
	int		i;
	int		j;
	char	**args;

	args = arg_expansion(&cmd, *shell);
	i = 1;
	while (args[i])
	{
		j = 0;
		while (shell->envp[j])
			j++;
		realloc_env(shell->envp, args[i], j + 1, shell);
		i++;
	}
	free_string_array(args);
	g_status = 0;
}
