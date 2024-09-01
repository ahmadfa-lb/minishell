/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_process_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:40:06 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/01 11:50:01 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_redirections(t_data *data, t_cmd *current_cmd)
{
	t_list_tokens	*redir;

	redir = current_cmd->list_redirectors;
	while (redir)
	{
	    redirect(data, redir->type, redir->next);
	    redir = redir->next;
	}
}

// void	handle_piping(int *pipe_fds, int nb_pipes)
// {
// 	if (nb_pipes > 0)
// 	{
// 		if (pipe(pipe_fds) == -1)
// 		{
// 			perror("pipe");
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// }

// pid_t	handle_forking(void)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (pid);
// }

int	execute_command(t_cmd *current_cmd, t_data *data)
{
	char	**arguments;

	arguments = build_arguments(current_cmd->tokens_list);
	if (execve(current_cmd->command_path, arguments, data->env_array) == -1)
	{
		perror("execve");
		free(arguments);
		exit(EXIT_FAILURE);
	}
	free(arguments);
	return (EXIT_SUCCESS);
}


// // int	execute_command(t_cmd *current_cmd, t_data *data)
// // {
// // 	char	**arguments;

// // 	arguments = build_arguments(current_cmd->tokens_list);
// // 	return (execve(current_cmd->command_path, arguments, data->env_array));
// // 	perror("execve");
// // 	free(arguments);
// // 	exit(EXIT_FAILURE);
// // }

// void	cleanup_fds(t_data *data)
// {
// 	dup2(data->saved_stdout, STDOUT_FILENO);
// 	dup2(data->saved_stdin, STDIN_FILENO);
// 	close(data->saved_stdout);
// 	close(data->saved_stdin);
// }