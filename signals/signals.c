/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <cdurro@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:39:18 by cdurro            #+#    #+#             */
/*   Updated: 2023/12/11 16:03:31 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		g_status = 128 + signal;
	}
	else if (signal == SIGQUIT)
	{
		printf("Quit (core dumped)");
		printf("\n");
		g_status = 128 + signal;
	}
}

void	handle_signal(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 128 + SIGINT;
	}
}

void	handle_here_doc_signal(int signal)
{
	if (signal == SIGINT)
	{
		g_status = 128 + SIGINT;
		ioctl(0, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
