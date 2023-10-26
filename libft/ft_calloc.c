/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:32:28 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:17:51 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	result;

	result = size * nmemb;
	if (nmemb && size != result / nmemb)
		return (NULL);
	ptr = (void *)malloc(result * sizeof(void));
	if (ptr != NULL)
		ft_memset(ptr, 0, result);
	return (ptr);
}
