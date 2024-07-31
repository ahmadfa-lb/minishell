/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:51:23 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:46:43 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
#include "../inc/libft.h"

int	ft_printf_d(int nb);
int	ft_printf_c(char c);
int	ft_printf_s(const char *str);
int	ft_printf_hex(unsigned int num, char x_case);
int	ft_printf_u(unsigned int nb);
int	ft_printf_p(void *p);
int	ft_printf(const char *format, ...);

#endif