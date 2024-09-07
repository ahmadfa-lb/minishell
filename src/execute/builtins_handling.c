/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 04:34:28 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 19:05:13 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(char *cmd, char **args, t_data *data)
{
	if (!ft_strcmp("echo", cmd))
		return (ft_echo(args));
	else if (!ft_strcmp("cd", cmd))
		return (ft_cd(args, data->env_list));
	else if (!ft_strcmp("pwd", cmd))
		return (ft_pwd());
	else if (!ft_strcmp("export", cmd))
		return (ft_export(&data->env_list, args));
	else if (!ft_strcmp("unset", cmd))
		return (ft_unset(&data->env_list, args));
	else if (!ft_strcmp("env", cmd))
		return (ft_env(data->env_list));
	else if (!ft_strcmp("exit", cmd))
		return (ft_exit(args));
	return (-1);
}

int	handle_builtin_command(t_cmd *current_cmd, t_data *data)
{
	char	*cmd;
	char	**args;
	int		result;

	cmd = current_cmd->tokens_list->value;
	args = build_arguments(current_cmd->tokens_list);
	if (!args)
		return (-1);
	result = execute_builtin(cmd, args, data);
	free_args(args);
	return (result);
}

bool	check_if_builtin(t_cmd *cmd_list)
{
	t_list_tokens	*tokens;
	char			*cmd_seq;

	tokens = cmd_list->tokens_list;
	if (!tokens)
		return (false);
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
