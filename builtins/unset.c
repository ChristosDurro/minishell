/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:21:54 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/09 15:24:36 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**unset_var(char *var, int space, t_shell *shell)
{
	int	i;
	int	j;
	char **new_envp;

	i = 0;
	j = 0;
	if (!env_exists(shell->envp, var))
		return (shell->envp);
	new_envp = malloc(sizeof(char *) * (space - 1));
	if (!new_envp)
		return (NULL);
	while (shell->envp[i] && shell->envp[j])
	{
		if (ft_strncmp(shell->envp[j], var, ft_strlen(var)) == 0 && shell->envp[j][ft_strlen(var)] == '=')
				j++;
		else
		{
			new_envp[i] = ft_strdup(shell->envp[j]);
			i++;
			j++;
		}
	}
	new_envp[i] = 0;
	free(shell->envp);
	return (new_envp);
}

void	unset(t_token *start, t_shell *shell)
{
	t_token	*current;
	int	i;
	int	j;

	if (start->next)
		current = start->next;
	else
		return ;
	while (current)
	{
		i = 0;
		j = 0;
		while (shell->envp[i])
			i++;
		shell->envp = unset_var(current->value, i, shell);
		current = current->next;
	}
}
