/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 06:14:19 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 19:58:40 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	swap_nodes(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_key = a->key;
	temp_value = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

int	check_key(char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_numcmp(const char *s1, const char *s2)
{
	int	len1;
	int	len2;

	if ((*s1 == '-' && *s2 != '-') || (*s1 != '-' && *s2 == '-'))
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len2 > len1)
		return (-1);
	else if (len2 < len1)
		return (1);
	else
		return (ft_strncmp(s1, s2, len1));
}

int	check_bounds(char *str)
{
	int		i;
	char	*s;

	i = 0;
	s = ft_strtrim(str, " \t\n");
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-')
	{
		if (ft_numcmp("-9223372036854775808", s) >= 0)
			return (free(s), 1);
		else
			return (free(s), 0);
	}
	else
	{
		if (ft_numcmp("9223372036854775807", s) >= 0)
			return (free(s), 1);
		else
			return (free(s), 0);
	}
}

int	calculate_exit_status(int status)
{
	int	res;

	res = status % 256;
	while (res < 0)
	{
		res += 256;
	}
	return (res);
}
