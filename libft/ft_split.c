/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:30:44 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:16:18 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	strcounter(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] != c && s[i] != '\0')
				i++;
			count++;
		}
	}
	return (count);
}

static void	fillarr(char **arr, size_t len_arr, char const *s, char c)
{
	size_t	i;
	size_t	len_word;

	i = 0;
	while (i < len_arr)
	{
		len_word = 0;
		while (*s == c && *s != 0)
			s++;
		while (s[len_word] != c && s[len_word] != '\0')
			len_word++;
		arr[i] = ft_substr(s, 0, len_word);
		s += len_word;
		i++;
	}
	arr[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t	len_arr;
	char	**arr;

	if (!s)
		return (0);
	len_arr = strcounter(s, c);
	arr = malloc(sizeof(char *) * (len_arr + 1));
	if (!arr)
		return (NULL);
	fillarr(arr, len_arr, s, c);
	return (arr);
}
