/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 15:21:37 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/17 02:44:23 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	find_start(char const *str, char const *set)
{
	int	start;

	start = 0;
	while (str[start] && is_in_set(str[start], set))
		start++;
	return (start);
}

int	find_end(char const *str, char const *set)
{
	int	end;

	end = ft_strlen(str) -1;
	while (end >= 0 && is_in_set(str[end], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*trimmed_str;
	int		i;

	start = find_start(s1, set);
	end = find_end(s1, set);
	if (start > end)
		return (ft_strdup(""));
	if (!s1 || !set)
		return (NULL);
	len = end - start + 1;
	trimmed_str = (char *)malloc(len + 1);
	if (!trimmed_str)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		trimmed_str[i] = s1[start];
		i++;
		start++;
	}
	trimmed_str[i] = '\0';
	return (trimmed_str);
}
