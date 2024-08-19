/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:29:16 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/17 02:44:23 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
	{
		len ++;
	}
	return (len);
}


int	ft_strlen1(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
	{
		len ++;
	}
	return (len);
}