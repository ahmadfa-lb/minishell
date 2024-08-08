/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 08:15:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/08 14:53:25 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_iswhitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void *ft_skip_spaces(char *str)
{
	while (ft_iswhitespace(*str))
		*str = *str + 1;
}

char *strndupp(const char *s, size_t n)
{
    size_t len = strnlen(s, n);
    char *new_str = malloc(len + 1);
    if (!new_str) return NULL; 
    strncpy(new_str, s, len);       
    new_str[len] = '\0';        
    return new_str;
}
