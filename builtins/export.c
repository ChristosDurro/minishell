/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 13:39:27 by cdurro            #+#    #+#             */
/*   Updated: 2024/01/13 12:33:53 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_len_till_equal(char *str)
{
	int		len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}

static int	wrong_chars_check(char *str)
{
	char	*before_equal;

	before_equal = ft_substr(str, 0, get_len_till_equal(str));
	if (ft_strchr(before_equal, '!')
		|| ft_strchr(before_equal, '`') || ft_strchr(before_equal, '@')
		|| ft_strchr(before_equal, '#') || ft_strchr(before_equal, '%')
		|| ft_strchr(before_equal, '^') || ft_strchr(before_equal, '&')
		|| ft_strchr(before_equal, '*') || ft_strchr(before_equal, '(')
		|| ft_strchr(before_equal, ')') || ft_strchr(before_equal, '-')
		|| ft_strchr(before_equal, '+') || ft_strchr(before_equal, '[')
		|| ft_strchr(before_equal, ']') || ft_strchr(before_equal, '{')
		|| ft_strchr(before_equal, '}') || ft_strchr(before_equal, ';')
		|| ft_strchr(before_equal, '\'') || ft_strchr(before_equal, '"')
		|| ft_strchr(before_equal, '<') || ft_strchr(before_equal, '>')
		|| ft_strchr(before_equal, ',') || ft_strchr(before_equal, '.')
		|| ft_strchr(before_equal, '?'))
	{
		free(before_equal);
		return (1);
	}
	free(before_equal);
	return (0);
}

static int	export_wrong_var_check(char *str, int *i)
{
	if (wrong_chars_check(str)
		|| (str[0] == '=' || ft_isdigit(str[0])
			|| (!ft_isalpha(str[0]) && str[0] != '_')))
	{
		write(2, str, ft_strlen(str));
		write(2, NOT_VALID, ft_strlen(NOT_VALID));
		(*i)++;
		g_status = 1;
		return (1);
	}
	return (0);
}

void	export(t_command cmd, t_shell *shell)
{
	int		i;
	int		j;
	char	**args;

	args = arg_expansion(&cmd, *shell);
	i = 1;
	while (args[i])
	{
		if (export_wrong_var_check(args[i], &i))
			continue ;
		if (!ft_strchr(args[i], '=') && i++)
			continue ;
		j = 0;
		while (shell->envp[j])
			j++;
		realloc_env(shell->envp, args[i], shell);
		i++;
	}
	free_string_array(args);
	if (g_status != 1)
		g_status = 0;
}
