/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:00:15 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:16:14 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*target;
	int		len;

	len = ft_strlen(s);
	target = malloc((len + 1) * sizeof(char));
	if (target == NULL)
		return (0);
	target[len] = '\0';
	len--;
	while (len >= 0)
	{
		target[len] = s[len];
		len--;
	}
	return (target);
}
