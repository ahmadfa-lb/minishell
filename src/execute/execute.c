/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/30 08:42:07 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_parent_process(t_data *data, int *in_fd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (data->nb_pipes > 0)
	{
		close(data->pipe_fds[1]);
		*in_fd = data->pipe_fds[0];
	}
}

void	wait_for_children(pid_t *pids, int count, t_data *data)
{
	int	status;
	int	j;

	j = 0;
	while(j < count)
	{
		waitpid(pids[j], &status, 0);
		data->exit_status = WEXITSTATUS(status);
		j++;
	}
}

void	handle_child_process(t_data *data, t_cmd *current_cmd, int in_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (data->nb_pipes > 0)
	{
		dup2(data->pipe_fds[1], STDOUT_FILENO);
		close(data->pipe_fds[1]);
		close(data->pipe_fds[0]);
	}
	execute_command(current_cmd, data);
}

void	initialize_command_execution(t_data *data, int *status, int *in_fd,
	 pid_t **pids)
{
	*status = 0;
	*in_fd = STDIN_FILENO;
	data->saved_stdout = dup(STDOUT_FILENO);
	data->saved_stdin = dup(STDIN_FILENO);
	*pids = malloc(sizeof(pid_t) * (data->nb_pipes + 1));
}

int	ft_execute_command(t_data *data, t_cmd *current_cmd)
{
	int		status;
	int		in_fd; 
	pid_t	*pids;
	int		i;

	(initialize_command_execution(data, &status, &in_fd, &pids), i = 0);
	while (current_cmd)
	{
		if (!ft_verify_if_cmd_is_valid(data, current_cmd))
		{
			current_cmd = current_cmd->next;
			continue;
		}
		(handle_redirections(data, current_cmd),handle_piping(data->pipe_fds,
		data->nb_pipes),pids[i] = handle_forking());
		if (pids[i] == 0) // Child process
			handle_child_process(data, current_cmd, in_fd);
		else // Parent process
			handle_parent_process(data, &in_fd);
		current_cmd = current_cmd->next;
		data->nb_pipes--;
		i++;
	}
	(wait_for_children(pids, i, data),free(pids),cleanup_fds(data));
	return (status);
}

