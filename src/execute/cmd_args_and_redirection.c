/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_and_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:29:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/30 08:39:55 by afarachi         ###   ########.fr       */
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