/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_args_and_redirection.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:29:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/13 16:37:19 by afarachi         ###   ########.fr       */
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
		arguments[i++] = ft_strdup(tokens_list->value);
		tokens_list = tokens_list->next;
	}
	arguments[i] = NULL;
	return (arguments);
}

int	open_and_duplicate(const char *filename, int flags, mode_t mode,
	int target_fd)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	redirect(t_data *data, t_tokens_type token, t_list_tokens *tokens_list)
{
	char	*name;
	int		res;

	name = NULL;
	res = 0;
	if (token == TOKEN_REDIRECT_OUT)
		res = open_and_duplicate(tokens_list->value,
				O_WRONLY | O_CREAT | O_TRUNC, 0644, STDOUT_FILENO);
	else if (token == TOKEN_REDIRECT_IN)
		res = open_and_duplicate(tokens_list->value, O_RDONLY, 0, STDIN_FILENO);
	else if (token == TOKEN_APPEND)
		res = open_and_duplicate(tokens_list->value,
				O_WRONLY | O_CREAT | O_APPEND, 0644, STDOUT_FILENO);
	else if (!data->cmd_list->next && token == TOKEN_HEREDOC)
	{
		name = handle_heredoc(data->cmd_list, data, tokens_list->quote_type);
		if (name)
		{
			printf("444444\n");
			res = open_and_duplicate(name, O_RDONLY, 0, STDIN_FILENO);
			free(name);
		}
	}
	return (res);
}

int	handle_redirections(t_data *data, t_cmd *current_cmd)
{
	t_list_tokens	*redir;

	redir = current_cmd->list_redirectors;
	while (redir)
	{
		if (redirect(data, redir->type, redir->next))
			return (0);
		redir = redir->next;
	}
	return (1);
}
