/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_and_cmd_validation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:34:35 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 19:06:06 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin_path(const char *dir, const char *cmd)
{
	char	*path;
	int		len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	path = malloc(len * sizeof(char));
	if (!path)
		return (NULL);
	ft_strcpy(path, dir);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}

char	*find_executable_in_paths(char **paths, t_cmd *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin_path(paths[i], cmd->tokens_list->value);
		if (!full_path)
			return (NULL);
		if (ft_is_executable(full_path))
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

bool	is_builtin_command(t_cmd *cmd_list)
{
	t_list_tokens	*tokens;
	char			*cmd_seq;

	tokens = cmd_list->tokens_list;
	cmd_seq = tokens->value;
	if (!ft_strcmp("cd", cmd_seq))
		return (true);
	else if (!ft_strcmp("export", cmd_seq))
		return (true);
	else if (!ft_strcmp("unset", cmd_seq))
		return (true);
	else if (!ft_strcmp("exit", cmd_seq))
		return (true);
	else
		return (false);
}

bool	ft_lookup_cmd_in_envpaths(t_data *data, t_cmd *cmd)
{
	char	**paths;
	char	*path_var;

	path_var = get_env(data->env_list, "PATH");
	if (!path_var)
		return (false);
	paths = ft_split(path_var, ':');
	if (!paths)
		return (false);
	cmd->command_path = find_executable_in_paths(paths, cmd);
	ft_free_split(paths);
	return (cmd->command_path != NULL);
}

bool	ft_verify_if_cmd_is_valid(t_data *data, t_cmd *cmd)
{
	char	*command;

	command = cmd->tokens_list->value;
	if (!command)
		return (true);
	if (!*command)
	{
		data->exit_status = 127;
		return (ft_print_error_message("'': ", "command not found"), false);
	}
	if (is_builtin_command(cmd))
		return (true);
	if (!ft_handle_direct_command(data, cmd, command))
		return (false);
	if (*command && !ft_lookup_cmd_in_envpaths(data, cmd))
	{
		data->exit_status = 127;
		return (ft_print_error_message(command, ": command not found"), false);
	}
	if (cmd->command_path)
		return (true);
	return (false);
}
