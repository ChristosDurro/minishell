/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 17:54:02 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:16:13 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_string_format(va_list args, t_print *print_struct)
{
	char	*string_ptr;
	size_t	i;

	i = 0;
	string_ptr = va_arg(args, char *);
	if ((print_struct->space == 1 && print_struct->width > 0)
		&& (ft_strncmp(string_ptr, "", ft_strlen(string_ptr)) == 0))
	{
		while (i++ < print_struct->width)
			ft_putchar(' ', print_struct);
	}
	else if (string_ptr == NULL)
		ft_putstr("(null)", print_struct);
	else if (print_struct->width > 0
		&& (ft_strlen(string_ptr) < print_struct->width))
	{
		i = 0;
		while (i++ < (print_struct->width - ft_strlen(string_ptr)))
			ft_putchar(' ', print_struct);
		ft_putstr(string_ptr, print_struct);
	}
	else
		ft_putstr(string_ptr, print_struct);
}
