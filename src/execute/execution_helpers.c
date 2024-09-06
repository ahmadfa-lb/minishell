/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 08:46:45 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	*create_forks(int len)
{
	int	*pids;
	int	i;

	pids = (int *)malloc(len * sizeof(int));
	if (!pids)
		return (NULL);
	i = 0;
	while (i < len)
	{
		pids[i] = -1;
		i++;
	}
	return (pids);
}

void	wait_pids_and_get_status(pid_t *pids, int num_pipes, int *last_status)
{
	int		status;
	pid_t	pid;
	int		i;
	int		flag;

	i = 0;
	status = 0;
	flag = 0;
	while (i < num_pipes + 1)
	{
		pid = waitpid(pids[i], &status, 0);
		if (pid == pids[num_pipes])
		{
			if (WIFEXITED(status) && !flag)
				*last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				*last_status = 128 + WTERMSIG(status);
				flag = 1;
			}
		}
		i++;
	}
}

void	give_status_value(int pid, int *last_status)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		*last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		*last_status = 128 + WTERMSIG(status);
	else
		*last_status = 1;
}

int	set_redirection_and_execute(t_data *data, t_cmd *current_cmd)
{
	int	stdin_copy;
	int	stdout_copy;
	int	status;

	status = 0;
	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (stdin_copy < 0 || stdout_copy < 0)
		(perror("minishell: "), exit(1));
	handle_redirections(data, current_cmd);
	status = handle_builtin_command(current_cmd, data);
	if (dup2(stdin_copy, STDIN_FILENO) < 0
		|| dup2(stdout_copy, STDOUT_FILENO) < 0)
		return (perror("minishell: "), (1));
	(close(stdin_copy), close(stdout_copy));
	return (status);
}

bool	ft_handle_direct_command(t_data *data, t_cmd *cmd, char *command)
{
	if (ft_strchr(command, '/') || !get_env(data->env_list, "PATH"))
	{
		if (!ft_check_file_status(command, data))
			return (false);
		cmd->command_path = ft_strdup(command);
		if (!cmd->command_path)
		{
			perror("error duplicating command");
			return (false);
		}
		return (true);
	}
	return (false);
}
