/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:20:16 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:53:06 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void	ft_putnb(unsigned int nb, int *len)
{
	if (nb >= 10)
		ft_putnb(nb / 10, len);
	*len += ft_printf_c((nb % 10) + '0');
}

int	ft_printf_u(unsigned int nb)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (write(1, "0", 1));
	ft_putnb(nb, &len);
	return (len);
}
