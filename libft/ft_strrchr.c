/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:29:51 by afarachi          #+#    #+#             */
/*   Updated: 2024/06/20 10:56:48 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	size_t			i;
	unsigned char	chr;

	chr = c;
	i = ft_strlen(s);
	str = (char *)s + i;
	if (c == '\0')
		return (str++);
	while (str >= s)
	{	
		if (*str == chr)
			return (str);
		str--;
	}
	str = NULL;
	return (str);
}
