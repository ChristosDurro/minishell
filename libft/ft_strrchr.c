/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:58:00 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:15:31 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if ((unsigned char)s[len] == (unsigned char)c)
		return ((char *)(s + len));
	while (len--)
	{
		if ((unsigned char)s[len] == (unsigned char)c)
			return ((char *)(s + len));
	}
	return (0);
}
