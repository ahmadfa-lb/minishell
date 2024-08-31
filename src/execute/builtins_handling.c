/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:34:28 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/31 06:11:01 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int handle_builtin_command(t_cmd *current_cmd, t_data *data)
{
    char *cmd = current_cmd->tokens_list->value;
    char **args = build_arguments(current_cmd->tokens_list);  // Assuming this function builds the args array

    if (!ft_strcmp("echo", cmd))
        return ft_echo(args);
    else if (!ft_strcmp("cd", cmd))
        return ft_cd(args, data->env_list);
    else if (!ft_strcmp("pwd", cmd))
        return ft_pwd();
    else if (!ft_strcmp("export", cmd))
        return ft_export(&data->env_list, args);
    else if (!ft_strcmp("unset", cmd))
        return ft_unset(&data->env_list, args); // Now just call ft_unset with the args array
    else if (!ft_strcmp("env", cmd))
        return ft_env(data->env_list);
    else if (!ft_strcmp("exit", cmd))
        return ft_exit(args);

    return -1; // Return a default error code if no built-in matches
}


bool	check_if_builtin(t_cmd *cmd_list)
{
	t_list_tokens	*tokens;
	char		*cmd_seq;

	tokens = cmd_list->tokens_list;
	cmd_seq = tokens->value;
	if (!ft_strcmp("echo", cmd_seq))
		return (true);
	else if (!ft_strcmp("cd", cmd_seq))
		return (true);
	else if (!ft_strcmp("pwd", cmd_seq))
		return (true);
	else if (!ft_strcmp("export", cmd_seq))
		return (true);
	else if (!ft_strcmp("unset", cmd_seq))
		return (true);
	else if (!ft_strcmp("env", cmd_seq))
		return (true);
	else if (!ft_strcmp("exit", cmd_seq))
		return (true);
	else
		return (false);
}