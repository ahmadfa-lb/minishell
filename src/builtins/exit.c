/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:27:26 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/06 14:10:39 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	check_status_str(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 		{
// 			return (0);
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int	calculate_exit_status(int status)
// {
// 	int	res;

// 	res = status % 256;
// 	while (res < 0)
// 	{
// 		res += 256;
// 	}
// 	return (res);
// }

// void	handle_too_many_args_error(void)
// {
// 	printf("exit: too many arguments\n");
// 	exit(1);
// }

// int	convert_and_validate_exit_status(char **arg)
// {
// 	long long	exit_status;

// 	if (!check_status_str(arg[1]))
// 	{
// 		printf("minishell: %s: numeric argument required\n", arg[1]);
// 		return (2);
// 	}
// 	if (arg[2] != NULL)
// 	{
// 		handle_too_many_args_error();
// 		return (1);
// 	}
// 	errno = 0;
// 	exit_status = ft_atoll(arg[1]);
// 	if (errno == ERANGE || exit_status > LONG_MAX || exit_status < LONG_MIN)
// 	{
// 		printf("minishell: %s: numeric argument required\n", arg[1]);
// 		return (2);
// 	}
// 	return (calculate_exit_status((int)exit_status));
// }

// int	ft_exit(char **args)
// {
// 	int	exit_status;

// 	if (args[1] != NULL)
// 		exit_status = convert_and_validate_exit_status(args);
// 	else
// 		exit_status = 0;
// 	return (exit(exit_status), exit_status);
// }


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
