/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 06:35:11 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/30 08:10:27 by afarachi         ###   ########.fr       */
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

int	open_and_duplicate(const char *filename, int flags, mode_t mode, int target_fd)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}


int	redirect(t_data *data,t_tokens_type token, t_list_tokens *tokens_list)
{
	//char	*name;
	//int		fd;

	//name = NULL;
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
void	handle_piping(int *pipe_fds, int nb_pipes)
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
pid_t	handle_forking()
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	execute_command(t_cmd *current_cmd, t_data *data)
{
	char	**arguments;

	arguments = build_arguments(current_cmd->tokens_list);
	execve(current_cmd->command_path, arguments, data->env_array);
	perror("execve");
	free(arguments);
	exit(EXIT_FAILURE);
}




void cleanup_fds(t_data *data)
{
    dup2(data->saved_stdout, STDOUT_FILENO);
    dup2(data->saved_stdin, STDIN_FILENO);
    close(data->saved_stdout);
    close(data->saved_stdin);
}

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
    for (int j = 0; j < count; j++)
    {
        waitpid(pids[j], &status, 0);
        data->exit_status = WEXITSTATUS(status);
    }
}

void handle_child_process(t_data *data, t_cmd *current_cmd, int in_fd)
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

void initialize_command_execution(t_data *data, int *status, int *in_fd, pid_t **pids, int *i)
{
    *status = 0;
    *in_fd = STDIN_FILENO;
    data->saved_stdout = dup(STDOUT_FILENO);
    data->saved_stdin = dup(STDIN_FILENO);
    *pids = malloc(sizeof(pid_t) * (data->nb_pipes + 1));
    *i = 0;
}

int ft_execute_command(t_data *data, t_cmd *current_cmd)
{
    int status;
    int in_fd; 
    pid_t *pids;
    int i;

    initialize_command_execution(data, &status, &in_fd, &pids, &i);
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

