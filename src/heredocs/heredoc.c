/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:55:56 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/04 14:21:22 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_heredoc_filename(void)
{
	static int	index;
	char		*filename;

	index = 0;
	filename = ft_strjoin("/tmp/heredoc_", ft_itoa(index++));
	return filename;
}

void	write_heredoc_to_file(const char *filename, const char *content)
{
    int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("open");
		return;
	}
	write(fd, content, ft_strlen(content));
	close(fd);
}

char	*read_heredoc_input(const char *delimiter)
{
    char	*line;
    char	*heredoc_content;
	char	*temp;

	heredoc_content = ft_strdup("");
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            free(heredoc_content);
            return NULL;
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        temp = ft_strjoin(heredoc_content, line);
        heredoc_content = temp;
        temp = ft_strjoin(heredoc_content, "\n");
        //free(heredoc_content);
        heredoc_content = temp;
        free(line);
    }
    return (heredoc_content);
}


char	*handle_heredoc(t_cmd *cmd, t_data *data)
{
	t_list_tokens	*redir_token;
	char			*heredoc_content;
	char			*filename;
	t_list_tokens	*heredoc_token;

	redir_token = cmd->list_redirectors;
	while (redir_token)
	{
	    if (redir_token->type == TOKEN_HEREDOC)
	    {
	        heredoc_content = read_heredoc_input(redir_token->next->value);
	        heredoc_token = create_token_node(TOKEN_WORD, NO_QUOTE, heredoc_content, false);
	        append_token(&data->first_tokens_list, heredoc_token);
	        data->first_tokens_list = dollar_expansion(data);
            heredoc_content = ft_strdup(heredoc_token->value);
            ft_free_node(&data->first_tokens_list, heredoc_token);
            filename = generate_heredoc_filename();
            write_heredoc_to_file(filename, heredoc_content); 
            free(heredoc_content);
            return (filename);
        }
        redir_token = redir_token->next;
    }
    return (NULL);
}