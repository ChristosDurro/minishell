/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:12:06 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 16:11:11 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_everything(t_shell *shell)
{
	int	i;

	if (shell->token_head)
		free_tokens(shell->token_head);
	i = -1;
	while (++i < shell->commands_num)
	{
		if (i == shell->redir_error_index)
			break ;
		if (shell->parse_error == 0
			|| (shell->parse_error == 2
				&& i < shell->redir_error_index)
			|| shell->parse_error == 3)
		{
			free(shell->commands[i].redirs);
			free(shell->commands[i].redir_types);
			free(shell->commands[i].args);
		}
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
