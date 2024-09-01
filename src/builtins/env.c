/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:05:48 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/01 10:04:35 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(t_env *env_list)
{
	t_env	*temp;

	temp = env_list;
	while (temp != NULL)
	{
		if (temp->hidden == 0)
			printf("%s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
	return (0);
}
