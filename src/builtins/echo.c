/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:49:48 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/04 22:49:55 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_valid_n_flag(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-' || arg[1] != 'n')
		return (false);
	while (arg[i] != '\0')
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	ft_echo(char **args)
{
	bool	newline;
	int		i;

	newline = true;
	i = 1;
	while (args[i] && is_valid_n_flag(args[i]))
	{
		newline = false;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
