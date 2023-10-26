/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:39:27 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/26 15:12:12 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export(t_token *start, t_shell *shell)
{
	t_token *current;
	int	i;
	char *tmp;

	if (start->next)
		current = start->next;
	else
		return ;

	while (current)
	{
		i = 0;
		while (shell->envp[i])
			i++;
		tmp = ft_strchr(current->value,'=');
		if (!tmp) {
			current = current->next;
			continue ;
		}
		realloc_env(shell->envp, current->value, i + 1, shell);
		current = current->next;
	}
}