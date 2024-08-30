/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 12:03:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/30 08:34:33 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_executable(const char *path)
{
	struct stat sb;

	if (stat(path, &sb) == 0 && sb.st_mode & S_IXUSR)
		return (true);
	return (false);
}

bool	ft_check_executable(char *input, t_data *data)
{
	if (access(input, X_OK) == -1)
	{
		data->exit_status = 126;
		ft_print_error_message(input, ": Permission denied");
		return (false);
	}
	return (true);
}

bool	ft_check_if_directory(char *input, t_data *data)
{
	struct stat	file_info;

	if (stat(input, &file_info) == -1)
	{
		perror("stat");
		return (true);
	}
	if (S_ISDIR(file_info.st_mode))
	{
		data->exit_status = 126;
		ft_print_error_message(input, ": is a directory");
		return (true);
	}
	return (false);
}

bool	ft_check_file_existence(char *input, t_data *data)
{
	if (access(input, F_OK) == -1)
	{
		data->exit_status = 127;
		ft_print_error_message(input, ": No such file or directory");
		return (false);
	}
	return (true);
}

bool	ft_check_file_status(char *input, t_data *data)
{
	if (!ft_check_file_existence(input, data))
		return (false);
	if (ft_check_if_directory(input, data))
		return (false);
	if (!ft_check_executable(input, data))
		return (false);
	return (true);
}