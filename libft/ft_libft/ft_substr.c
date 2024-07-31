/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 14:31:27 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:46:11 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	check_len(size_t s_len, unsigned int start, size_t len)
{
	size_t	mlen;

	mlen = s_len - (size_t)start;
	if (mlen > len)
		mlen = len;
	return (mlen);
}

char	*check_alloc(size_t max_len)
{
	char	*s_str;

	s_str = (char *)malloc(max_len + 1);
	if (s_str == NULL)
		return (NULL);
	return (s_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	size_t	max_len;
	char	*sub_str;
	char	*empty_str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		empty_str = ft_strdup("");
		return (empty_str);
	}
	max_len = check_len(s_len, start, len);
	sub_str = check_alloc(max_len);
	i = 0;
	while (i < max_len && s[start + i] != '\0')
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	size_t	i;
// 	size_t	s_len;
// 	size_t	max_len;
// 	char	*sub_str;
// 	char	*empty_str;

// 	if (!s)
// 		return (NULL);
// 	s_len = ft_strlen(s);
// 	if (start >= s_len)
// 	{
// 		empty_str = ft_strdup("");
// 		return (empty_str);
// 	}
// 	max_len = s_len - start;
// 	if (max_len > len)
// 		max_len = len;
// 	sub_str = (char *)malloc(max_len + 1);
// 	if (sub_str == NULL)
// 		return (NULL);
// 	i = 0;
// 	while (i < max_len && s[start + i] != '\0')
// 	{
// 		sub_str[i] = s[start + i];
// 		i++;
// 	}
// 	sub_str[i] = '\0';
// 	return (sub_str);
// }