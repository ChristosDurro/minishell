/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:23:41 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:17:46 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_hex_format(char c, t_print *print_struct, unsigned int u_converted)
{
	if (c == 'x')
		ft_putunbr_base(u_converted, "0123456789abcdef", print_struct);
	else
		ft_putunbr_base(u_converted, "0123456789ABCDEF", print_struct);
}
