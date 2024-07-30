/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:59:27 by afarachi          #+#    #+#             */
/*   Updated: 2024/06/12 13:57:55 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_sep(char c, char delimiter)
{
	if (c == delimiter)
		return (1);
	else
		return (0);
}

int	count_words(char const *str, char delimiter)
{
	int	count;
	int	word;
	int	i;

	count = 0;
	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (check_sep(str[i], delimiter))
			word = 0;
		else if (!word)
		{
			word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

void	strncpy_custom(char *dest, char const *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

void	split(char const *str, char delimiter, char **list)
{
	int			i;
	char const	*word_start;
	int			word_length;

	i = 0;
	while (*str)
	{
		if (!check_sep(*str, delimiter))
		{
			word_start = str;
			while (*str && !check_sep(*str, delimiter))
				str++;
			word_length = str - word_start;
			list[i] = (char *)malloc((word_length + 1) * sizeof(char));
			strncpy_custom(list[i], word_start, word_length);
			list[i][word_length] = '\0';
			i++;
		}
		else
			str++;
	}
	list[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**list;

	list = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	split(s, c, list);
	return (list);
}
