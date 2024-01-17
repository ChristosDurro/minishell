/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 19:15:53 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/12 18:09:57 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	init_expand_vars(int *i, int *j, char *quote)
{
	*j = -1;
	*i = 0;
	*quote = '\0';
}

int	quote_val(char c, char *quote)
{
	if ((c == '"' || c == '\'') && !(*quote))
	{
		*quote = c;
		return (1);
	}
	else if (c && c == *quote)
	{
		*quote = '\0';
		return (1);
	}
	return (0);
}

char	*expansion_util(char *tmp, char *str, int *j, t_shell shell)
{
	int	len;

	len = 0;
	free(tmp);
	tmp = ft_itoa(shell.previous_status);
	while (*(str + *j + 2 + len) && (*(str + *j + 2 + len) != '$'
			&& *(str + *j + 2 + len) != '\'' && *(str + *j + 2 + len) != '"'))
		len++;
	(*j) += ft_strlen("$?") + len - 1;
	return (construct_str(tmp, ft_substr(str, *j - len + 1, len)));
}

char	*expansion_util2(char *tmp, char *str, int *j, t_shell shell)
{
	char	*env;

	free(tmp);
	env = ft_strdup(expand(str + *j, j, shell));
	(*j)--;
	return (env);
}

char	*construct_str(char *code, char *after_code)
{
	char	*tmp3;

	tmp3 = ft_strjoin(code, after_code);
	free(code);
	free(after_code);
	return (tmp3);
}
