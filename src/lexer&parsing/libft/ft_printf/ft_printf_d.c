/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:19:57 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:53:06 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_printf_d(int nb)
{
	char	*s;
	int		ctr;

	s = ft_itoa(nb);
	if (!s)
		return (0);
	ft_putstr_fd(s, 1);
	ctr = ft_strlen(s);
	free(s);
	return (ctr);
}
