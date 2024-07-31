/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:36:51 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:53:06 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	put_pointer(unsigned long long num, int *len)
{
	if (num >= 16)
	{
		put_pointer(num / 16, len);
		put_pointer(num % 16, len);
	}
	else
	{
		if (num > 9)
			*len += ft_printf_c(num - 10 + 'a');
		else
			*len += ft_printf_c(num + '0');
	}
}

int	ft_printf_p(void *p)
{
	int					len;
	unsigned long long	num;

	num = (unsigned long long) p;
	len = 0;
	if (num == 0)
		return (write(1, "(nil)", 5));
	len += write(1, "0x", 2);
	put_pointer(num, &len);
	return (len);
}
