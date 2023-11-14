/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:12:06 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:14:31 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_everything(t_shell *shell)
{
	int	i;
	int	j;
	int	k;

	if (shell->token_head)
		free_tokens(shell->token_head);
	i = -1;
	while (++i < shell->commands_num)
	{
		free(shell->commands[i].args);
	}
	free(shell->commands);
}

void	free_envp(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
		free(shell->envp[i]);
	free(shell->envp);
}

void	free_string_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
