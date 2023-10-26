/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdurro <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:39:45 by cdurro            #+#    #+#             */
/*   Updated: 2023/06/26 10:16:42 by cdurro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "./libft.h"

typedef struct s_print
{
	size_t	width;
	int		space;
	int		plus;
	int		dash;
	int		total_length;
}		t_print;

int		ft_check_base(char *base);
int		ft_printf(const char *str, ...);

void	ft_initialise(t_print *print_struct);
void	ft_putchar(char c, t_print *print_struct);
void	ft_putstr(char *str, t_print *print_struct);
void	ft_string_format(va_list args, t_print *print_struct);
void	ft_integer_format(t_print *print_struct, int i_converted);
void	ft_unsigned_format(va_list args, t_print *print_struct);
void	ft_pointer_format(va_list args, t_print *print_struct);
void	ft_hex_format(char c, t_print *print_struct, unsigned int u_converted);
void	ft_putnbr(int nbr, t_print *print_struct);
void	ft_putunbr_base(unsigned int nbr, char *base, t_print *print_struct);
void	ft_putlnbr_base(unsigned long nbr, char *base, t_print *print_struct);

#endif
