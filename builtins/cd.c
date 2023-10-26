/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 12:22:45 by cdurro            #+#    #+#             */
/*   Updated: 2023/10/09 15:28:01 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd(t_token *start, t_shell *shell)
{
	t_token *current;
	char	*new_str;
	int	new_len;

	if (start->next)
		current = start->next;
	else
		return ;
	// if cd . then change to current directory
	if (ft_strncmp(current->value, ".", 1) == 0)
		chdir(shell->cwd);
	// if cd .. then change to previous directory
	else if (ft_strncmp(current->value, "..", 2) == 0)
	{
		shell->cwd = getcwd(shell->cwd, 256);
		// printf("%s\n", shell->cwd);
		// printf("len of cwd: %zu\n", ft_strlen(shell->cwd));
		new_str = ft_strrchr(shell->cwd, '/');
		printf("%s\n", new_str);
		// printf("len of new_str: %zu\n", ft_strlen(new_str));
		new_len = ft_strlen(shell->cwd) - ft_strlen(new_str);
		new_str = ft_substr(shell->cwd, 0, new_len);
		// printf("new str again: %s\n", new_str);
		chdir(new_str);
	}
	// if cd ~ then change to home directory
	else if (ft_strncmp(current->value, "~", 1) == 0)
	{
		new_str = getenv("HOME");
		chdir(new_str);
	}
	// if cd some_path then change to that specific directory
	else
	{
		chdir(current->value);
	}
}
