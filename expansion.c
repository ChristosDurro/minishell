/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:11:01 by cdurro            #+#    #+#             */
/*   Updated: 2023/11/14 09:14:53 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**arg_expansion(t_command *cmd, t_shell shell)
{
	int		i;
	int		j;
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

static char	*expansion_logic(char *str, int *j, t_shell shell)
{
	char	*env;

	if (ft_strncmp(str + *j, "$?", 2) == 0)
		return ("$");
	env = expand(str + *j, j, shell);
	(*j)--;
	return (env);
}

char	*expand2(char *str, t_shell shell)
{
	char	*ret;
	char	quote;
	int		j;
	int		i;

	ret = ft_calloc(4096, sizeof(char));
	j = -1;
	i = 0;
	quote = '\0';
	while (str[++j])
	{
		if ((str[j] == '"' || str[j] == '\'') && !quote)
			quote = str[j];
		else if (str[j] && str[j] == quote)
			quote = '\0';
		else if (str[j] && str[j] == '$' && (quote == '"' || !quote))
		{
			i += ft_strlcat(ret, expansion_logic(str, &j, shell), 4096);
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
