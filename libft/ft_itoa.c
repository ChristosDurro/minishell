/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:29:02 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:17:25 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_chars(int n)
{
	int	chars;

	if (n > 0)
		chars = 0;
	else
		chars = 1;
	while (n != 0)
	{
		chars++;
		n /= 10;
	}
	return (chars);
}

void	solution(char *number, int *digits, int *n)
{
	int	stop;

	number[*digits] = '\0';
	(*digits)--;
	if (*n == -2147483648)
	{
		number[*digits] = '8';
		(*digits)--;
		*n /= 10;
	}
	if (*n >= 0)
		stop = 0;
	else
		stop = 1;
	if (*n < 0)
		*n = (*n) * -1;
	while (*digits >= stop)
	{
		number[*digits] = (*n % 10) + '0';
		*n /= 10;
		(*digits)--;
	}
	if (stop == 1)
		number[*digits] = '-';
}

char	*ft_itoa(int n)
{
	char	*number;
	int		digits;

	digits = get_chars(n);
	number = malloc((digits + 1) * sizeof(char));
	if (!number)
		return (NULL);
	solution(number, &digits, &n);
	return (number);
}
