/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 13:48:01 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/26 15:42:12 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**set_env(char **ev)
{
	char **ev_list;
	int	i;

	i = 0;
	while (ev[i])
		i++;
	ev_list = malloc(sizeof(char *) * (i + 1));
	if (!ev_list)
		return (NULL);
	i = 0;
	while (ev[i])
	{
		ev_list[i] = ev[i];
		i++;
	}
	ev_list[i] = 0;
	return (ev_list);
}

char	*get_env(char *str, t_shell shell)
{
	char *env;
	int	i;

	while (shell.envp[i])
	{
		if(ft_strnstr(shell.envp[i], str, ft_strlen(str)))
			return (shell.envp[i] + ft_strlen(str) + 1);
		i++;
	}
	return (NULL);
}

int	env_exists(char **ev, char *val)
{
	int i;

	i = 0;
	while (ev[i])
	{
		if (ft_strncmp(ev[i], val, ft_strlen(val)) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	change_env(char *new_var, t_shell *shell)
{
	int i;
	int j;
	int k;
	int total_len;
	char **new_input;
	
	new_input = ft_split(new_var, '=');
	i = 0;
	total_len = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], new_input[0], ft_strlen(new_input[0])) == 0)
		{
			// printf("envp[%d] before: %s\n", i, shell->envp[i]);
			j = 0;
			while (new_input[j])
			{
				k = 0;
				while(new_input[j][k] && new_input[j][k] != '$')
					k++;
				total_len += ft_strlen(ft_substr(new_input[j], 0, k)) + 1;
				j++;
			}
			if (new_var[total_len - 1] == '$')
				total_len--;
			shell->envp[i] = ft_substr(new_var, 0, total_len);
			// printf("envp[%d] after: %s\n", i, shell->envp[i]);
			free(new_input);
			return ;
		}
		i++;
	}
}

void	realloc_env(char **ev, char *new_var, int space, t_shell *shell)
{
	int	i;
	int	j;
	int	k;
	char **new_input;
	char *tmp;

	shell->envp = malloc(sizeof(char *) * (space + 1));
	if (!shell->envp)
		return ;
	i = 0;
	while (ev[i])
	{
		shell->envp[i] = 0;
		i++;
	}
	shell->envp[i++] = 0;
	shell->envp[i++] = 0;
	i = 0;
	while (ev[i])
	{
		shell->envp[i] = ev[i];
		i++;
	}
	if (new_var[ft_strlen(new_var) - 1] == '=') {
		shell->envp[i] = new_var;
		return;
	}
	new_input = ft_split(new_var, '=');
	if (new_input[0][0] == '$' || new_input[1][0] == '$')
		return ;
	if (env_exists(shell->envp, new_input[0]))
	{
		change_env(new_var, shell);
		return ;
	}
	j = 0;
	while (new_input[0][j] && ft_isalnum(new_input[0][j]) || new_input[0][j] == '_')
		j++;
	new_input[0] = ft_substr(new_input[0], 0, j);
	k = 0;
	while (new_input[k] && new_input[k][0] != '$')
	{
		if (new_input[k + 1] != NULL)
			tmp = ft_strjoin(new_input[k], "=");
		else
			tmp = ft_strjoin("", new_input[k]);
		if (k == 0)
			shell->envp[i] = ft_strjoin("", tmp);
		else
			shell->envp[i] = ft_strjoin(shell->envp[i], tmp);
		k++;
	}
	i++;
	shell->envp[i] = 0;
}
/// [RANDOM]=[random]=[random]=[random]=[random]=[afkafsa]

void	print_envp(t_token *start, t_shell shell)
{
	int	i;

	if (start->next)
	{
		printf("env: too many arguments!\n");
		return;
	}
	i = 0;
	while (shell.envp[i])
	{
		printf("%s\n", shell.envp[i]);
		i++;
	}
}