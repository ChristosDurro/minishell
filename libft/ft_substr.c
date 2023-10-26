/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:35:22 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:15:27 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub_len = ft_strlen(s + start);
	if (sub_len >= len)
		sub_len = len;
	sub = malloc((sub_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	sub[sub_len] = 0;
	while (sub_len-- > 0)
		sub[sub_len] = s[sub_len + start];
	return (sub);
}
