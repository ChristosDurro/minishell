/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 16:46:25 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/15 16:46:41 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand3(char *str, t_shell shell)
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
		if (str[j] && str[j] == '$')
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
