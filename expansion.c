/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:11:01 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 16:45:39 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_expansion(t_command *cmd, t_shell shell)
{
	int		i;
	char	**ret;

	i = 0;
	while (cmd->args[i])
		i++;
	ret = malloc(sizeof(char *) * (i + 2));
	ret[i + 1] = 0;
	while (i > 0)
	{
		ret[i] = expand2(cmd->args[i - 1], shell);
		i--;
	}
	ret[i] = expand2(cmd->cmd, shell);
	return (ret);
}

void	init_tmps(char **tmp, char **tmp2, char *str, int *j)
{
	int	len;

	len = 0;
	while (*(str + *j + 1 + len) && (ft_isalnum(*(str + *j + 1 + len))
			|| *(str + *j + 1 + len) == '_' || *(str + *j + 1 + len) == '?'))
		len++;
	*tmp = ft_substr(str + *j, 0, len + 1);
	len = 0;
	while (*(str + *j + 1 + len) && (ft_isalnum(*(str + *j + 1 + len))
			|| *(str + *j + 1 + len) == '_'))
		len++;
	*tmp2 = ft_substr(str + *j, 0, len + 1);
}

char	*expansion_logic(char *str, int *j, t_shell shell)
{
	char	*tmp;
	char	*tmp2;

	init_tmps(&tmp, &tmp2, str, j);
	if (ft_strncmp(tmp, "$?", 2) == 0)
		return (free(tmp2), expansion_util(tmp, str, j, shell));
	else if (env_exists(shell.envp, tmp2 + 1))
		return (expansion_util2(tmp2, str, j, shell));
	else if (ft_strncmp(tmp, "$", 1) == 0 && ft_strlen(tmp) == 1)
	{
		free(tmp);
		free(tmp2);
		(*j) += ft_strlen("$") - 1;
		return (ft_strdup("$"));
	}
	else
	{
		(*j) += ft_strlen(tmp2) - 1;
		free(tmp);
		free(tmp2);
		return (ft_strdup(""));
	}
}

char	*expand2(char *str, t_shell shell)
{
	char	*ret;
	char	quote;
	char	*tmp;
	int		j;
	int		i;

	ret = ft_calloc(4096, sizeof(char));
	init_expand_vars(&i, &j, &quote);
	while (str[++j])
	{
		if (quote_val(str[j], &quote))
			continue ;
		else if (str[j] && str[j] == '$' && (quote == '"' || !quote))
		{
			tmp = expansion_logic(str, &j, shell);
			i += ft_strlcat(ret, tmp, 4096);
			free(tmp);
			if (i > 0)
				while (ret[i - 1] == '\0')
					i--;
		}
		else
			ret[i++] = str[j];
	}
	return (ret);
}

char	*expand(char *str, int *k, t_shell shell)
{
	char	*env;
	char	*tmp;
	int		i;
	int		len;

	len = ft_strlen(str);
	i = 1;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	tmp = ft_substr(str, 0, i);
	*k += ft_strlen(tmp);
	env = get_env(tmp + 1, shell);
	free(tmp);
	if (!env)
		return ("");
	return (env);
}
