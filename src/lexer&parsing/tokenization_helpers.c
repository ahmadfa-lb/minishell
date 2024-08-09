/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:15:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/09 14:49:36 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void ft_skip_whitespace(char **input)
{
    while (ft_isspace(**input))
        (*input)++;
}

char *ft_strncpy(char *dest, const char *src, size_t n) 
{
    size_t i;

	i = 0;
    while (i < n)
	{
        if (src[i] != '\0') 
            dest[i] = src[i];
		else
            dest[i] = '\0';
        i++;
    }
    return (dest);
}

char *ft_strcpy(char *dest, const char *src)
{
    char *dest_ptr;
	
	dest_ptr = dest;
    while (*src)
        *dest_ptr++ = *src++;
    *dest_ptr = '\0';
    return (dest);
}

char *ft_strcat(char *dest, const char *src)
{
    char *dest_ptr;
	
	dest_ptr = dest;
    while (*dest_ptr)
        dest_ptr++;
    while (*src)
        *dest_ptr++ = *src++;
    *dest_ptr = '\0';
    return (dest);
}


size_t ft_strnlen(const char *str, size_t n)
{
    size_t length;
	
	length = 0;
    while (length < n && str[length] != '\0')
        length++;
    return (length);
}

char *ft_strndup(const char *s, size_t n)
{
    size_t len = ft_strnlen(s, n);
    char *new_str = malloc(len + 1);
    if (!new_str) return NULL; 
	ft_strncpy(new_str, s, len);       
    new_str[len] = '\0';        
    return new_str;
}
