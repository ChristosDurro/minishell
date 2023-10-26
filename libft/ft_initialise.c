/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:23:47 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:17:44 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_initialise(t_print *print_struct)
{
	print_struct->width = 0;
	print_struct->space = 0;
	print_struct->plus = 0;
	print_struct->dash = 0;
	print_struct->total_length = 0;
}
