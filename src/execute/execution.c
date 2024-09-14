/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/14 11:45:57 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_in_child(t_data *data, t_cmd *current_cmd)
{
	char	**cmd;

	if (!handle_redirections(data, current_cmd))
		exit(1);
	if (!(current_cmd->tokens_list))
		exit(0);
	if (check_if_builtin(current_cmd))
		exit(handle_builtin_command(current_cmd, data));
	if (!ft_verify_if_cmd_is_valid(data, current_cmd))
		exit(data->exit_status);
	cmd = build_arguments(current_cmd->tokens_list);
	if (execve(current_cmd->command_path, cmd, data->env_array) == -1)
	{
		ft_print_error_message("minishell: ", strerror(errno));
		free_args(cmd);
		exit(1);
	}
}

// int	execute_cmds_in_childs(t_data *data, t_cmd *current_cmd, int num_pipes)
// {
// 	int		**pipes;
// 	int		i;
// 	int		*pids;

// 	pids = create_forks(num_pipes + 1);
// 	pipes = create_pipes(num_pipes);
// 	i = 0;
// 	set_execution_signals();
// 	while (current_cmd)
// 	{	
// 		pids[i] = fork();
// 		if (pids[i] == 0)
// 		{
// 			reset_signals();
// 			if (herdoc_detected(current_cmd)) 
// 			{	
// 				handle_heredoc_for_cmd(data, current_cmd);
// 			}
			
// 			set_pipes(current_cmd, pipes, i, num_pipes);
// 			execute_in_child(data, current_cmd);
// 		}
// 		else
// 			close_parent_pipe(current_cmd, pipes, i);
// 		current_cmd = current_cmd->next;
// 		i++;
// 	}
// 	wait_pids_and_get_status(pids, num_pipes, &(data->exit_status));
// 	(close_all_pipes(pipes, num_pipes), free_pipes(pipes, num_pipes));
// 	return (free(pids), data->exit_status);
// }

int	execute_cmds_in_childs(t_data *data, t_cmd *current_cmd, int num_pipes)
{
	int		**pipes;
	int		i;
	int		*pids;
	int		heredoc_pid = -1;  // To store the PID of the heredoc handler

	pids = create_forks(num_pipes + 1);
	pipes = create_pipes(num_pipes);
	i = 0;
	set_execution_signals();
	while (current_cmd)
	{	
		pids[i] = fork();
		if (pids[i] == 0)
		{
			reset_signals();
			if (herdoc_detected(current_cmd)) 
			{	
				handle_heredoc_for_cmd(data, current_cmd);
			 	// exit(EXIT_SUCCESS);
			}
			set_pipes(current_cmd, pipes, i, num_pipes);
			execute_in_child(data, current_cmd);
		}
		else
		{
			if (herdoc_detected(current_cmd))
			{
				heredoc_pid = pids[i];  // Store the heredoc PID
				waitpid(heredoc_pid, &data->exit_status, 0);  // Wait for the heredoc process to complete
			}
			close_parent_pipe(current_cmd, pipes, i);
		}
		current_cmd = current_cmd->next;
		i++;
	}
	wait_pids_and_get_status(pids, num_pipes, &(data->exit_status));
	(close_all_pipes(pipes, num_pipes), free_pipes(pipes, num_pipes));
	return (free(pids), data->exit_status);
}


void	exec_one_non_builtin_cmd(t_data *data, t_cmd *current_cmd)
{
	char	**cmd;

	if (!handle_redirections(data, current_cmd))
		exit(1);
	if (!(current_cmd->tokens_list))
		exit(0);
	cmd = build_arguments(current_cmd->tokens_list);
	if (!cmd)
		exit(1);
	if (!ft_verify_if_cmd_is_valid(data, current_cmd))
		(free_args(cmd), exit(data->exit_status));
	if (execve(current_cmd->command_path, cmd, data->env_array) == -1)
	{
		ft_print_error_message("minishell: ", strerror(errno));
		free_args(cmd);
		exit(1);
	}
}

int	execute_cmd_in_parent(t_data *data, t_cmd *current_cmd)
{
	pid_t	pid;

	if (check_if_builtin(current_cmd)
		&& !ft_strncmp("exit", current_cmd->tokens_list->value, 4))
		printf("exit\n");
	if (check_if_builtin(current_cmd))
		return (set_redirection_and_execute(data, current_cmd));
	pid = fork();
	set_execution_signals();
	if (pid == 0)
		exec_one_non_builtin_cmd(data, current_cmd);
	else
		give_status_value(pid, &(data->exit_status));
	return (data->exit_status);
}


int	ft_execute_command(t_data *data, t_cmd *current_cmd)
{
	int		num_pipes;
	int		status;

	num_pipes = get_num_pipes(current_cmd);
	if (num_pipes == 0)
		return (0);
	num_pipes--;
	if (num_pipes == 0)
	{
		status = execute_cmd_in_parent(data, current_cmd);
		set_signals();
		return (status);
	}
	status = execute_cmds_in_childs(data, current_cmd, num_pipes);
	set_signals();
	return (status);
}
