/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/29 09:43:16 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**build_arguments(t_list_tokens *tokens_list)
{
	int				count;
	t_list_tokens	*tmp;
	char			**arguments;
	int				i;

	count = 0;
	tmp = tokens_list;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	arguments = malloc(sizeof(char *) * (count + 1));
	if (!arguments)
		return (NULL);
	i = 0;
	while (tokens_list)
	{
		arguments[i++] = tokens_list->value;
		tokens_list = tokens_list->next;
	}
	arguments[i] = NULL;
	return (arguments);
}

int	ft_lstsize1(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

bool	ft_verify_if_cmd_is_valid(t_data *data, t_cmd *cmd)
{
	char	*command;
	char	*path_env;

	command = cmd->tokens_list->value;
	if (!command)
		return (false);
	if (ft_strchr(command, '/') || !(path_env = get_env(data->env_list, "PATH")))
	{
		if (!ft_check_file_status(command, data))
			return (false);
		cmd->command_path = ft_strdup(command);
		if (!cmd->command_path)
			return (perror("error duplicating command"), false);
		return (true);
	}
	
	if (*command && !ft_lookup_cmd_in_envpaths(data, cmd))
	{
		ft_print_error_message(command, ": command not found");
		data->exit_status = 127;
		return (false);
	}
	if (cmd->command_path) // Use command_path for execution
		return (true);
	return (false);
}

int ft_execute_command(t_data *data)
{
    int status = 0;
    int parser_length;
    int nb_pipes;
    int pipe_fds[2];
    int in_fd = STDIN_FILENO;
    t_cmd *current_cmd;
    pid_t pid;

    parser_length = ft_lstsize1(data->cmd_list);
    nb_pipes = parser_length - 1;

    current_cmd = data->cmd_list;

    while (current_cmd)
    {
        // Validate the command before execution
        if (!ft_verify_if_cmd_is_valid(data, current_cmd))
        {
            current_cmd = current_cmd->next;
            continue;
        }
        // return (data->exit_status);

        // Create a pipe if there are still more commands
        if (nb_pipes > 0)
        {
            if (pipe(pipe_fds) == -1)
            {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        // Fork the process
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) // Child process
        {
            // Handle input redirection from the previous command's pipe
            if (in_fd != STDIN_FILENO)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            // Handle output redirection to the next command's pipe
            if (nb_pipes > 0)
            {
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[1]);
                close(pipe_fds[0]);
            }

            // Execute the command
            char **arguments = build_arguments(current_cmd->tokens_list);
            execve(current_cmd->command_path, arguments, data->env_array);
            perror("execve");
            free(arguments);
            exit(EXIT_FAILURE);
        }
        else // Parent process
        {
            // Close pipe ends not needed by the parent
            if (in_fd != STDIN_FILENO)
                close(in_fd);
            if (nb_pipes > 0)
            {
                close(pipe_fds[1]);
                in_fd = pipe_fds[0]; // Next command reads from this pipe
            }

            // Wait for the child process to finish
            waitpid(pid, &status, 0);
            data->exit_status = WEXITSTATUS(status);
        }

        current_cmd = current_cmd->next;
        nb_pipes--;
    }

    return status;
}


