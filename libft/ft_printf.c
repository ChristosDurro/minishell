/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:37:41 by cdurro            #+#    #+#             */
/*   Updated: 2023/05/22 15:24:49 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include<stdio.h>

static void	ft_bonus_dash(va_list va, const char *str, t_print *print_struct)
{
	unsigned int	u_converted;

	u_converted = va_arg(va, unsigned int);
	if (u_converted == 0)
	{
		ft_putchar('0', print_struct);
		return ;
	}
	if (*(str - 1) == '#')
	{
		if (*str == 'x')
			ft_putstr("0x", print_struct);
		if (*str == 'X')
			ft_putstr("0X", print_struct);
		ft_hex_format(*str, print_struct, u_converted);
	}
	else
		ft_hex_format(*str, print_struct, u_converted);
}

static void	ft_bonus_integers(va_list va, t_print *print_struct)
{
	int	i_converted;

	i_converted = va_arg(va, int);
	if (i_converted >= 0)
	{
		if (print_struct->plus == 1)
			ft_putchar('+', print_struct);
		else if (print_struct->plus == 0 && print_struct->space == 1)
			ft_putchar(' ', print_struct);
	}
	ft_integer_format(print_struct, i_converted);
}

static void	ft_flag_skip(const char *str, t_print *print_struct, int *index)
{
	while (*str == '#' || *str == ' ' || *str == '+')
	{
		if (*str == '+')
			print_struct->plus = 1;
		if (*str == ' ')
			print_struct->space = 1;
		str++;
		*index += 1;
	}
}

static void	ft_format(va_list va, const char *str,
					t_print *print_struct, int *index)
{
	ft_flag_skip(str, print_struct, index);
	str = str + *index;
	print_struct->width += ft_atoi(str);
	while (ft_isdigit(*(str++)))
		*index += 1;
	str--;
	if (*str == 'c')
		ft_putchar(va_arg(va, int), print_struct);
	else if (*str == 's')
		ft_string_format(va, print_struct);
	else if (*str == 'i' || *str == 'd')
		ft_bonus_integers(va, print_struct);
	else if (*str == 'p')
		ft_pointer_format(va, print_struct);
	else if (*str == 'u')
		ft_unsigned_format(va, print_struct);
	else if (*str == 'x' || *str == 'X')
		ft_bonus_dash(va, str, print_struct);
	else
		ft_putchar('%', print_struct);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	t_print	print_struct;
	int		index;

	va_start(args, str);
	ft_initialise(&print_struct);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			index = 0;
			ft_format(args, str, &print_struct, &index);
			str = str + index;
		}
		else
			ft_putchar(*str, &print_struct);
		str++;
	}
	va_end(args);
	return (print_struct.total_length);
}
