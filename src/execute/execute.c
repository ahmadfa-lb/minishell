/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/29 15:49:46 by afarachi         ###   ########.fr       */
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

int open_and_duplicate(const char *filename, int flags, mode_t mode, int target_fd)
{
    int fd;

    // Open the file with the specified flags and mode
    fd = open(filename, flags, mode);
    if (fd == -1)
    {
        perror("open");
        return -1; // Return an error code if opening the file fails
    }

    // Duplicate the file descriptor to the target file descriptor
    if (dup2(fd, target_fd) == -1)
    {
        perror("dup2");
        close(fd);
        return -1; // Return an error code if duplicating the file descriptor fails
    }
    dup2(fd, STDIN_FILENO);
    // Close the original file descriptor, as it is no longer needed
    close(fd);
    return 0; // Return success
}


int	redirect(t_data *data,t_tokens_type token, t_list_tokens *tokens_list)
{
	char	*name;
	//int		fd;

	name = NULL;
	if (token == TOKEN_REDIRECT_OUT)
		open_and_duplicate(tokens_list->value, O_WRONLY | O_CREAT | O_TRUNC,
			0644, STDOUT_FILENO);
	else if (token == TOKEN_REDIRECT_IN)
		open_and_duplicate(tokens_list->value, O_RDONLY, 0, STDIN_FILENO);
	else if (token == TOKEN_APPEND)
		open_and_duplicate(tokens_list->value, O_WRONLY | O_CREAT | O_APPEND,
			0644, STDOUT_FILENO);
	// else if (token = TOKEN_HEREDOC)
	// 	name = handle_heredoc();
	// if (name)
	// {
	// 	fd = open(name, O_RDONLY);
	// 	if (fd > 0)
	// 		
	// 	close(fd);
	// }
	return (data->exit_status);
	
}



// int ft_execute_command(t_data *data)
// {
//     int status = 0;
//     int parser_length;
//     int nb_pipes;
//     int pipe_fds[2];
//     int in_fd = STDIN_FILENO;
//     t_cmd *current_cmd;
//     pid_t pid;
//     int saved_stdout = dup(STDOUT_FILENO); // Save original STDOUT
//     int saved_stdin = dup(STDIN_FILENO);   // Save original STDIN

//     parser_length = ft_lstsize1(data->cmd_list);
//     nb_pipes = parser_length - 1;

//     current_cmd = data->cmd_list;

//     while (current_cmd)
//     {
//         // Validate the command before execution
//         if (!ft_verify_if_cmd_is_valid(data, current_cmd))
//         {
//             current_cmd = current_cmd->next;
//             continue;
//         }

//         // Handle redirections
//         t_list_tokens *redir = current_cmd->list_redirectors;
//         while (redir)
//         {
//             redirect(data, redir->type, redir->next);
//             redir = redir->next;
//         }

//         // Create a pipe if there are still more commands
//         if (nb_pipes > 0)
//         {
//             if (pipe(pipe_fds) == -1)
//             {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         }

//         // Fork the process
//         pid = fork();
//         if (pid == -1)
//         {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         }
//         else if (pid == 0) // Child process
//         {
//             // Handle input redirection from the previous command's pipe
//             if (in_fd != STDIN_FILENO)
//             {
//                 dup2(in_fd, STDIN_FILENO);
//                 close(in_fd);
//             }

//             // Handle output redirection to the next command's pipe
//             if (nb_pipes > 0)
//             {
//                 dup2(pipe_fds[1], STDOUT_FILENO);
//                 close(pipe_fds[1]);
//                 close(pipe_fds[0]);
//             }

//             // Execute the command
//             char **arguments = build_arguments(current_cmd->tokens_list);
//             execve(current_cmd->command_path, arguments, data->env_array);
//             perror("execve");
//             free(arguments);
//             exit(EXIT_FAILURE);
//         }
//         else // Parent process
//         {
//             // Close pipe ends not needed by the parent
//             if (in_fd != STDIN_FILENO)
//                 close(in_fd);
//             if (nb_pipes > 0)
//             {
//                 close(pipe_fds[1]);
//                 in_fd = pipe_fds[0]; // Next command reads from this pipe
//             }

//             // Wait for the child process to finish
//             waitpid(pid, &status, 0);
//             data->exit_status = WEXITSTATUS(status);
//         }

//         // Restore the original STDOUT and STDIN
//         dup2(saved_stdout, STDOUT_FILENO);
//         dup2(saved_stdin, STDIN_FILENO);

//         current_cmd = current_cmd->next;
//         nb_pipes--;
//     }

//     // Close the saved file descriptors as they are no longer needed
//     close(saved_stdout);
//     close(saved_stdin);

//     return status;
// }

void handle_redirections(t_data *data, t_cmd *current_cmd)
{
    t_list_tokens *redir = current_cmd->list_redirectors;
    while (redir)
    {
        redirect(data, redir->type, redir->next);
        redir = redir->next;
    }
}
void handle_piping(int *pipe_fds, int nb_pipes)
{
    if (nb_pipes > 0)
    {
        if (pipe(pipe_fds) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }
}
pid_t handle_forking()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    return pid;
}
void execute_command(t_cmd *current_cmd, t_data *data)
{
    char **arguments = build_arguments(current_cmd->tokens_list);
    execve(current_cmd->command_path, arguments, data->env_array);
    perror("execve");
    free(arguments);
    exit(EXIT_FAILURE);
}
void handle_parent_process(int *in_fd, int *pipe_fds, int nb_pipes, int *status, t_data *data, pid_t pid)
{
    if (*in_fd != STDIN_FILENO)
        close(*in_fd);
    if (nb_pipes > 0)
    {
        close(pipe_fds[1]);
        *in_fd = pipe_fds[0];
    }
    waitpid(pid, status, 0);
    data->exit_status = WEXITSTATUS(*status);
}
void restore_file_descriptors(int saved_stdout, int saved_stdin)
{
    dup2(saved_stdout, STDOUT_FILENO);
    dup2(saved_stdin, STDIN_FILENO);
}
int ft_execute_command(t_data *data)
{
    int status = 0, nb_pipes, pipe_fds[2];
    int in_fd = STDIN_FILENO;
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    t_cmd *current_cmd = data->cmd_list;
    nb_pipes = ft_lstsize1(data->cmd_list) - 1;
    pid_t *pid = malloc(sizeof(pid_t) * (nb_pipes + 1));

    while (current_cmd)
    {
        if (!ft_verify_if_cmd_is_valid(data, current_cmd))
        {
            current_cmd = current_cmd->next;
            continue;
        }

        handle_redirections(data, current_cmd);
        handle_piping(pipe_fds, nb_pipes);
        pid = handle_forking();

        if (pid == 0) // Child process
        {
            if (in_fd != STDIN_FILENO)
            {
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }
            if (nb_pipes > 0)
            {
                dup2(pipe_fds[1], STDOUT_FILENO);
                close(pipe_fds[1]);
                close(pipe_fds[0]);
            }
            execute_command(current_cmd, data);
        }
        // else{
            
        // }

        restore_file_descriptors(saved_stdout, saved_stdin);
        current_cmd = current_cmd->next;
        nb_pipes--;
    }
    handle_parent_process(&in_fd, pipe_fds, nb_pipes, &status, data, pid);

    close(saved_stdout);
    close(saved_stdin);
    return status;
}
