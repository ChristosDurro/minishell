/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:48:01 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/10 12:05:43 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env(char **ev, t_shell *shell)
{
	int	i;

	shell->envp = ft_calloc(sizeof(char *), 4096);
	if (!shell->envp)
		return ;
	i = 0;
	while (ev[i])
	{
		shell->envp[i] = ft_strdup(ev[i]);
		i++;
	}
}

char	*get_env(char *str, t_shell shell)
{
	char	*env;
	int		i;

	i = 0;
	while (shell.envp[i])
	{
		if (ft_strnstr(shell.envp[i], str, ft_strlen(str)))
			return (shell.envp[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);
}

int	env_exists(char **ev, char *val)
{
	int		i;
	int		len;
	char	*tmp;

	len = 0;
	while (val[len] && val[len] != '=')
		len++;
	tmp = ft_substr(val, 0, len);
	len = ft_strlen(tmp);
	i = 0;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], tmp, len) == 0 && ev[i][len] == '=')
		{
			free(tmp);
			return (1);
		}
		i++;
	}
	free(tmp);
	return (0);
}

void	change_env(char *new_var, t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (new_var[j] && new_var[j] != '=')
		j++;
	tmp = ft_substr(new_var, 0, j);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], tmp, ft_strlen(tmp)) == 0)
			break ;
		i++;
	}
	free(shell->envp[i]);
	shell->envp[i] = ft_strdup(new_var);
	free(tmp);
}

void	realloc_env(char **ev, char *new_var, int space, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while (ev[i])
		i++;
	if (env_exists(shell->envp, new_var))
	{
		change_env(new_var, shell);
		return ;
	}
	free(shell->envp[i]);
	shell->envp[i] = ft_strdup(new_var);
	i++;
	shell->envp[i] = 0;
}
