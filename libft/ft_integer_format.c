/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_integer_format.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:10:25 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:17:41 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_integer_format(t_print *print_struct, int i_converted)
{
	if (i_converted == 0)
		ft_putchar('0', print_struct);
	else
		ft_putnbr(i_converted, print_struct);
}
