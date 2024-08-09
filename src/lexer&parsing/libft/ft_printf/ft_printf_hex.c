/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:20:09 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:53:06 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_hex(unsigned int num, int *len, char x_case)
{
	if (num >= 16)
	{
		put_hex(num / 16, len, x_case);
		put_hex(num % 16, len, x_case);
	}
	else
	{
		if (x_case == 'x')
		{
			if (num > 9)
				*len += ft_printf_c(num - 10 + 'a');
			else
				*len += ft_printf_c(num + '0');
		}
		else if (x_case == 'X')
		{
			if (num > 9)
				*len += ft_printf_c(num - 10 + 'A');
			else
				*len += ft_printf_c(num + '0');
		}
	}
}

int	ft_printf_hex(unsigned int num, char x_case)
{
	int	len;

	len = 0;
	if (num == 0)
		return (write(1, "0", 1));
	put_hex(num, &len, x_case);
	return (len);
}
