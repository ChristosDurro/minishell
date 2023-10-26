/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 10:05:22 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:15:29 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const *set, const char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static void	skip_characters(char const *set, const char *s1,
							size_t *i, size_t *s1_len)
{
	while (in_set(set, s1[*i]))
		(*i)++;
	if (s1[*i] == '\0')
		return ((void) NULL);
	while (in_set(set, s1[*s1_len - 1]))
		(*s1_len)--;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	s1_len;
	size_t	i;
	size_t	j;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	i = 0;
	skip_characters(set, s1, &i, &s1_len);
	len = s1_len - i + 1;
	trimmed = malloc(len * sizeof(char));
	if (!trimmed)
		return (NULL);
	j = 0;
	while (i < s1_len)
	{
		trimmed[j] = s1[i];
		j++;
		i++;
	}
	trimmed[j] = '\0';
	return (trimmed);
}
