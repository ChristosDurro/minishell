/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:04:40 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/10 14:02:56 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pwd(t_shell shell, int fd)
{
	char	*tmp;

	tmp = ft_strjoin(shell.cwd, "\n");
	ft_putstr_fd(tmp, fd);
	free(tmp);
	g_status = 0;
}
