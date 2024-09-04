/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:55:56 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/04 09:32:25 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_heredoc(t_list_tokens *heredoc_token, bool quotes, t_data *data, char *file_name, bool *stop_heredoc)
{
	int		fd;
	char	*line;

	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error opening heredoc file");
		return (EXIT_FAILURE);
	}

	line = readline("> ");
	while (line && strcmp(heredoc_token->value, line) != 0 && !(*stop_heredoc))
	{
		if (!quotes)
		{
			// Call your expander function here, if implemented.
			line = expander_str(data, line);
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);

	if (*stop_heredoc || !line)
	{
		close(fd);
		return (EXIT_FAILURE);
	}

	close(fd);
	return (EXIT_SUCCESS);
}

int	ft_heredoc(t_data *data, t_list_tokens *heredoc_token, char *file_name, bool *stop_heredoc)
{
	bool	quotes;
	int		sl;

	sl = EXIT_SUCCESS;
	quotes = (heredoc_token->quote_type == DOUBLE_QUOTE || heredoc_token->quote_type == SINGLE_QUOTE);

	// Remove surrounding quotes if they exist
	if (quotes)
	{
		delete_quotes(heredoc_token->value, '\"');
		delete_quotes(heredoc_token->value, '\'');
	}

	*stop_heredoc = 0;
	sl = create_heredoc(heredoc_token, quotes, data, file_name, stop_heredoc);

	return (sl);
}

char *generate_heredoc_filename(void)
{
	static int i = 0;
	char *num;
	char *file_name;

	num = ft_itoa(i++); // Assuming you have an ft_itoa implementation.
	file_name = ft_strjoin("/tmp/heredoc_", num); // Assuming you have an ft_strjoin implementation.
	free(num);
	return (file_name);
}

int handle_heredoc(t_data *data, t_cmd *cmd)
{
	t_list_tokens	*start;
	int				sl;
	char			*file_name;
	bool			stop_heredoc = false;

	start = cmd->list_redirectors;
	sl = EXIT_SUCCESS;

	while (cmd->list_redirectors)
	{
		if (cmd->list_redirectors->type == TOKEN_HEREDOC)
		{
			file_name = generate_heredoc_filename();
			sl = ft_heredoc(data, cmd->list_redirectors, file_name, &stop_heredoc);
			if (sl)
			{
				data->exit_status = 1;
				free(file_name);
				return (EXIT_FAILURE);
			}

			// Store the heredoc filename in the command's structure
			cmd->command_path = file_name;
		}
		cmd->list_redirectors = cmd->list_redirectors->next;
	}

	cmd->list_redirectors = start;
	return (EXIT_SUCCESS);
}