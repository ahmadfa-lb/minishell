/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 09:59:27 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 14:46:11 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	count_words(const char *s, char c)
{
	size_t	i;
	int		count;
	int		in_word;

	i = 0;
	count = 0;
	in_word = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (in_word)
			{
				count++;
				in_word = 0;
			}
		}
		else
			in_word = 1;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

static void	split(char **result, const char *s, char c)
{
	char	*word_start;
	char	*str;
	int		i;
	int		word_length;

	i = 0;
	str = (char *)s;
	while (*str)
	{
		if (*str != c)
		{
			word_start = str;
			while (*str && *str != c)
				str++;
			word_length = str - word_start + 1;
			result[i] = (char *)malloc(word_length);
			ft_strlcpy(result[i], word_start, word_length);
			i++;
		}
		else
			str++;
	}
	result[i] = NULL;
}

char	**ft_split(const char *s, char c)
{
	char	**result;

	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	split(result, s, c);
	return (result);
}
