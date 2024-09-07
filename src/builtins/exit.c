/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:27:26 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/06 19:58:30 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_status_str(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	handle_too_many_args_error(void)
{
	printf("exit: too many arguments\n");
	exit(1);
}

int	convert_and_validate_exit_status(char **arg)
{
	if (!check_status_str(arg[1]))
	{
		printf("minishell: %s: numeric argument required\n", arg[1]);
		return (2);
	}
	if (arg[2] != NULL)
	{
		handle_too_many_args_error();
		return (1);
	}
	if (!check_bounds(arg[1]))
	{
		printf("minishell: %s: numeric argument required\n", arg[1]);
		return (2);
	}
	return ((unsigned char)ft_atoi(arg[1]));
}

int	ft_exit(char **args)
{
	int	exit_status;

	if (args[1] != NULL)
		exit_status = convert_and_validate_exit_status(args);
	else
		exit_status = 0;
	return (exit(exit_status), exit_status);
}
