/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:05:48 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/01 10:46:04 by mouhamad_kr      ###   ########.fr       */
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
			printf("%s=\"%s\"\n"X, temp->key, temp->value);
		temp = temp->next;
	}
	printf("\n");
	return (0);
}
