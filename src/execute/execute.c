/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/28 07:00:41 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **build_arguments(t_list_tokens *tokens_list)
{
    int count = 0;
    t_list_tokens *tmp = tokens_list;

    // Count the number of tokens
    while (tmp)
    {
        count++;
        tmp = tmp->next;
    }

    // Allocate memory for the arguments array (+1 for NULL at the end)
    char **arguments = malloc(sizeof(char *) * (count + 1));
    if (!arguments)
        return NULL; // Handle malloc failure

    // Populate the arguments array
    int i = 0;
    while (tokens_list)
    {
        arguments[i++] = tokens_list->value; // Point to the value of the current token
        tokens_list = tokens_list->next;
    }
    arguments[i] = NULL; // Null-terminate the array

    return arguments;
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

int ft_execute_command(t_data *data)
{
    int status;
    int parser_length;
    int nb_pipes;
    int pipe_fds[2];
    int in_fd = STDIN_FILENO;
    t_cmd *current_cmd;
    pid_t pid;

    parser_length = ft_lstsize1(data->cmd);
    nb_pipes = parser_length - 1;

    current_cmd = data->cmd;

    if (parser_length == 1)
    {
        if (!ft_check_file_status(current_cmd->tokens_list->value, data))
            return (data->exit_status);

        char **arguments = build_arguments(current_cmd->tokens_list);
        execve(current_cmd->tokens_list->value, arguments, data->env_array);
        perror("execve");
        free(arguments); // Free the allocated memory
        exit(EXIT_FAILURE);
    }

    while (current_cmd)
    {
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
            // Handle input redirection from previous command's pipe
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
            if (!ft_check_file_status(current_cmd->tokens_list->value, data))
            {
                exit(data->exit_status);
            }
            char **arguments = build_arguments(current_cmd->tokens_list);
            execve(current_cmd->tokens_list->value, arguments, data->env_array);
            perror("execve");
            free(arguments); // Free the allocated memory
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

