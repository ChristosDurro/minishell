/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:18:46 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:15:19 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_unsigned_format(va_list args, t_print *print_struct)
{
	unsigned int	u_converted;

	u_converted = va_arg(args, unsigned int);
	if (u_converted == 0)
		ft_putchar('0', print_struct);
	else
		ft_putunbr_base(u_converted, "0123456789", print_struct);
}
