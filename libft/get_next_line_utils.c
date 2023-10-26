/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:57:36 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:15:17 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (s2[0] == '\0')
		return (0);
	joined = malloc(sizeof(char) * (ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1));
	if (!joined)
		return (0);
	i = 0;
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j] && s2[j] != '\n')
		joined[i++] = s2[j++];
	if (s2[j] == '\n')
		joined[i++] = '\n';
	joined[i] = '\0';
	if (s1)
		free(s1);
	return (joined);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	if (s && s[i] == '\n')
		i++;
	return (i);
}

int	ft_clean(char *str)
{
	int	i;
	int	j;
	int	is_nl;

	i = 0;
	j = 0;
	is_nl = 0;
	while (str[i])
	{
		if (is_nl)
			str[j++] = str[i];
		if (str[i] == '\n')
			is_nl = 1;
		str[i++] = '\0';
	}
	return (is_nl);
}
