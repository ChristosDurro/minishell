/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:35:04 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/05 12:38:44 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 4) == 0 && ft_strlen(str) == 4)
		return (1);
	else if (ft_strncmp(str, "pwd", 3) == 0 && ft_strlen(str) == 3)
		return (1);
	else if (ft_strncmp(str, "cd", 2) == 0 && ft_strlen(str) == 2)
		return (1);
	else if (ft_strncmp(str, "env", 3) == 0 && ft_strlen(str) == 3)
		return (1);
	else if (ft_strncmp(str, "export", 6) == 0 && ft_strlen(str) == 6)
		return (1);
	else if (ft_strncmp(str, "unset", 5) == 0 && ft_strlen(str) == 5)
		return (1);
	else if (ft_strncmp(str, "exit", 4) == 0 && ft_strlen(str) == 4)
		return (1);
	return (0);
}
