/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/19 02:10:36 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strnlen(const char *str, size_t n)
{
	size_t length;
	
	length = 0;
	while (length < n && str[length] != '\0')
		length++;
	return (length);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t len;
	char *new_str;

	len = ft_strnlen(s, n);
	new_str = malloc(len + 1);
	if (!new_str)
		return NULL; 
	ft_strncpy(new_str, s, len);       
	new_str[len] = '\0';        
	return (new_str);
}
