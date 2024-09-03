/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/03 05:24:28 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_parent_process(t_data *data, int *in_fd)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	if (data->nb_pipes > 0)
	{
		close(data->pipe_fds[1]);
		*in_fd = data->pipe_fds[0];
	}
}

void wait_for_children(pid_t *pids, int count, t_data *data)
{
	int status;
	int	copy;
	int j;

	j = 0;
	copy = 0;
	while (j < count)
	{
		waitpid(pids[j], &status, 0);
		copy = WEXITSTATUS(status);
		j++;
	}
	data->exit_status = copy;
}

int handle_child_process(t_data *data, t_cmd *current_cmd, int in_fd)
{
	int status;

	status = 0;
	if (current_cmd->next != NULL)
		dup2(data->pipe_fds[1], STDOUT_FILENO); // Redirect STDOUT to pipe

	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO); // Redirect STDIN from the input pipe
	}
	// Close unused pipe ends in the child process
	// close(in_fd);
	close(data->pipe_fds[0]);
	close(data->pipe_fds[1]);

	if (check_if_builtin(current_cmd))
		status = handle_builtin_command(current_cmd, data);
	else
		status = execute_command(current_cmd, data);
	exit(status);
}

void initialize_command_execution(t_data *data, int *status, pid_t **pids)
{
	*status = 0;

	// Save the original stdin and stdout
	data->saved_stdin = dup(STDIN_FILENO);
	if (data->saved_stdin == -1)
	{
		perror("dup saved_stdin");
		exit(EXIT_FAILURE);
	}

	data->saved_stdout = dup(STDOUT_FILENO);
	if (data->saved_stdout == -1)
	{
		perror("dup saved_stdout");
		exit(EXIT_FAILURE);
	}

	*pids = malloc(sizeof(pid_t) * (data->nb_pipes + 1));
	if (*pids == NULL)
	{
		perror("malloc pids");
		exit(EXIT_FAILURE);
	}
}

// int ft_execute_command(t_data *data, t_cmd *current_cmd)
// {
// 	int status;
// 	int in_fd;
// 	pid_t *pids;
// 	int i;

// 	in_fd = STDIN_FILENO;
// 	(initialize_command_execution(data, &status, &pids), i = 0);
// 	if (data->nb_pipes == 0) // Single command, no pipes
// 	{
// 		if (ft_verify_if_cmd_is_valid(data, current_cmd))
// 		{
// 			if (check_if_builtin(current_cmd))
// 				status = handle_builtin_command(current_cmd, data);
// 			else
// 			{
// 				pids[i] = handle_forking();

// 				if (pids[i] == 0) // Child process
// 				{
// 					if (dup2(in_fd, STDIN_FILENO) == -1) // Ensure stdin is properly set
// 					{
// 						perror("dup2");
// 						exit(EXIT_FAILURE);
// 					}
// 					status = execute_command(current_cmd, data);
// 					exit(status);
// 				}
// 				else // Parent process
// 				{
// 					waitpid(pids[i], &status, 0);
// 					data->exit_status = WEXITSTATUS(status);
// 				}
// 			}
// 		}
// 	}
// 	else
// 	{
// 		while (current_cmd)
// 		{
// 			if (!ft_verify_if_cmd_is_valid(data, current_cmd))
// 			{
// 				current_cmd = current_cmd->next;
// 				continue;
// 			}
// 			// Handle redirections before anything else
// 			handle_redirections(data, current_cmd);
// 			// Handle piping if more than one command
// 			handle_piping(data->pipe_fds, data->nb_pipes);

// 			if (check_if_builtin(current_cmd))
// 			{
// 				// Fork if the built-in is part of a pipeline
// 				if (data->nb_pipes > 0)
// 				{
// 					pids[i] = handle_forking();
// 					if (pids[i] == 0) // Child process
// 						status = handle_child_process(data, current_cmd, in_fd);
// 					else // Parent process
// 						handle_parent_process(data, &in_fd);
// 				}
// 				else
// 				{
// 					status = handle_builtin_command(current_cmd, data);
// 					data->exit_status = status;
// 				}
// 			}
// 			else
// 			{
// 				// Handle external commands with piping and redirection
// 				pids[i] = handle_forking();
// 				if (pids[i] == 0) // Child process
// 					handle_child_process(data, current_cmd, in_fd);

// 				else // Parent process
// 					handle_parent_process(data, &in_fd);
// 			}
// 			current_cmd = current_cmd->next;
// 			data->nb_pipes--;
// 			i++;
// 		}
// 	}
// 	(wait_for_children(pids, i, data), free(pids), cleanup_fds(data));
// 	return (status);
// }

int ft_execute_command(t_data *data, t_cmd *current_cmd)
{
	int status;
	int in_fd;
	pid_t *pids;
	int i;

	in_fd = STDIN_FILENO;
	(initialize_command_execution(data, &status, &pids), i = 0);
	if (data->nb_pipes == 0) // Single command, no pipes
	{
			if (check_if_builtin(current_cmd))
				status = handle_builtin_command(current_cmd, data);
			else
			{

				pids[i] = handle_forking();
				if (pids[i] == 0) // Child process
				{
					// if (current_cmd->tokens_list->value &&
					// 	(current_cmd->tokens_list->value[0] == ' ' || current_cmd->tokens_list->value[0] == '\0'))
					// {
					// 	// ft_print_error_message(current_cmd->tokens_list->value, ": command not found");
					// 	exit(127);
					// }
					if (!ft_verify_if_cmd_is_valid(data, current_cmd))
						exit(data->exit_status);
					if (dup2(in_fd, STDIN_FILENO) == -1) // Ensure stdin is properly set
					{
						perror("dup2");
						exit(EXIT_FAILURE);
					}
					status = execute_command(current_cmd, data);
					exit(status);
				}
				else // Parent process
				{
					waitpid(pids[i], &status, 0);
					return (WEXITSTATUS(status));
					// printf("%d\n", data->exit_status);
				}
		}
	}
	else
	{
		while (current_cmd)
		{
			// Handle redirections before anything else
			handle_redirections(data, current_cmd);
			// Handle piping if more than one command
			handle_piping(data->pipe_fds, data->nb_pipes);

			if (check_if_builtin(current_cmd))
			{
				// Fork if the built-in is part of a pipeline
				if (data->nb_pipes > 0)
				{
					pids[i] = handle_forking();
					if (pids[i] == 0) // Child process
						status = handle_child_process(data, current_cmd, in_fd);
					else // Parent process
						handle_parent_process(data, &in_fd);
				}
				else
				{
					status = handle_builtin_command(current_cmd, data);
					data->exit_status = status;
				}
			}
			else
			{
				// Handle external commands with piping and redirection
				pids[i] = handle_forking();
				if (pids[i] == 0) // Child process
				{
					if (!ft_verify_if_cmd_is_valid(data, current_cmd))
						exit(data->exit_status);	
					handle_child_process(data, current_cmd, in_fd);
				}

				else // Parent process
					handle_parent_process(data, &in_fd);
			}
			current_cmd = current_cmd->next;
			data->nb_pipes--;
			i++;
		}
	}
	(wait_for_children(pids, i, data), free(pids), cleanup_fds(data));
	// printf("%d\n", data->exit_status);
	return (data->exit_status);
}
