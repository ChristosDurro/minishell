/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:00:53 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/09 12:47:30 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_term(t_termios *term_backup, t_shell shell)
{
	t_termios term;
	char	*term_type;

	term_type = get_env("TERM", shell);
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1; // 1 바이트씩 처리
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		return (ENOTTY);
	return (0);
}

void	reset_term(t_termios *term_backup)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, term_backup) == -1)
		printf("Error reseting term");
}