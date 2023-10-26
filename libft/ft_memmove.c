/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:00:57 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:16:52 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destination;
	char	*source;

	if (!src && !dest)
		return (NULL);
	destination = (char *)dest;
	source = (char *)src;
	if (src > dest)
		while (n--)
			*destination++ = *source++;
	else
	{
		destination += n - 1;
		source += n - 1;
		while (n--)
			*destination-- = *source--;
	}
	return (dest);
}
