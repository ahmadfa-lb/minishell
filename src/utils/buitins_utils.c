/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buitins_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabbas <moabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 06:14:19 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 20:50:46 by moabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long		ft_atoll(const char *str)
{
	int			i;
	int			f;
	long long	out;

	i = 0;
	f = 1;
	out = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			f = -1;
		++i;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		out = out * 10 + (str[i] - '0');
		++i;
	}
	return (f * out);
}

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

void	sort_env_list(t_env *head)
{
	int		swapped;
	t_env	*ptr1;
	t_env	*lptr;

	lptr = NULL;
	if (head == NULL)
		return ;
	do
	{
		swapped = 0;
		ptr1 = head;
		while (ptr1->next != lptr)
		{
			if (strcmp(ptr1->key, ptr1->next->key) > 0)
			{
				swap_nodes(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
	while (swapped);
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