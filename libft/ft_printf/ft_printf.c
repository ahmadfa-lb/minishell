/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:43:36 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:53:06 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	check(char c, va_list args)
{
	if (c == 'c')
		return (ft_printf_c(va_arg(args, int)));
	else if (c == 's')
		return (ft_printf_s(va_arg(args, const char *)));
	else if (c == 'p')
		return (ft_printf_p(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_printf_d(va_arg(args, int)));
	else if (c == 'u')
		return (ft_printf_u(va_arg(args, unsigned int)));
	else if (c == 'x')
		return (ft_printf_hex(va_arg(args, int), 'x'));
	else if (c == 'X')
		return (ft_printf_hex(va_arg(args, int), 'X'));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, format);
	i = 0;
	len = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1] != '\0')
		{
			len += check(format[i + 1], args);
			i++;
		}
		else
			len += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
