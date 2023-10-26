/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:11:25 by cdurro            #+#    #+#             */
/*   Updated: 2023/05/19 17:42:50 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, t_print *print_struct)
{
	long	nbr;

	nbr = n;
	if (nbr < 0)
	{
		ft_putchar('-', print_struct);
		nbr = -nbr;
	}
	if (nbr >= 10)
	{
		ft_putnbr(nbr / 10, print_struct);
		ft_putchar((nbr % 10) + '0', print_struct);
	}
	else
		ft_putchar(nbr + '0', print_struct);
}
