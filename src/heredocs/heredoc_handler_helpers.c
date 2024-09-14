/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:29:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/14 11:49:23 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list_tokens	*parse_input_to_tokens(char *delimiter)
{
	t_list_tokens	*tokens;
	t_list_tokens	*new_node;
	char			*line;
	int				delimiter_len;

	tokens = NULL;
	delimiter_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (ft_strncmp(line, delimiter, delimiter_len) == 0)
			return (free(line), tokens);
		line = ft_strjoin(line, "\n");
		new_node = create_token_node(TOKEN_WORD, NO_QUOTE, line, 1);
		(append_token(&tokens, new_node), free(line));
	}
	return (tokens);
}


int	get_delimiters_count(t_list_tokens *redirectors)
{
	int	del_count;

	del_count = 0;
	while (redirectors)
	{
		if (redirectors->type == TOKEN_HEREDOC)
			del_count++;
		redirectors = redirectors->next;
	}
	return (del_count);
}

void	update_heredoc_data(t_list_tokens **heredoc_tokens, t_data *data,
	t_quote_type quote_type)
{
	if (!heredoc_tokens)
		return ;
	if (quote_type == SINGLE_QUOTE || quote_type == DOUBLE_QUOTE)
		return ;
	*heredoc_tokens = dollar_expansion(*heredoc_tokens, data);
}

int	herdoc_detected(t_cmd *current_cmd)
{
	t_list_tokens	*redirectors;

	if (!current_cmd)
		return (0);
	redirectors = current_cmd->list_redirectors;
	while (redirectors)
	{
		if (redirectors->type == TOKEN_HEREDOC)
			return (1);
		redirectors = redirectors->next;		
	}
	return (0);
}

// void	handle_heredoc_for_cmd(t_data *data, t_cmd *cmd)
// {
// 	char	*herdoc_file;
// 	int		fd;
	
// 	herdoc_file = NULL;
// 	if (herdoc_detected(cmd))
// 	{
// 		while (cmd->list_redirectors)
// 		{
// 			if (cmd->list_redirectors->type == TOKEN_HEREDOC)
// 			{
// 				herdoc_file = handle_heredoc(cmd, data,
// 					cmd->list_redirectors->next->quote_type);
// 				if (herdoc_file)
// 				{
// 					fd = open(herdoc_file, O_RDONLY);
// 					if (fd != -1)
// 						(dup2(fd, STDIN_FILENO), close(fd));
// 					free(herdoc_file);
// 				}
// 				// break ;
// 			}
// 			handle_redirections(data, cmd);
// 			cmd->list_redirectors = cmd->list_redirectors->next;
// 		}
// 	}
// }

int	handle_redirections_after_heredoc(t_data *data, t_cmd *current_cmd)
{
	t_list_tokens	*redir;

	redir = current_cmd->list_redirectors;
	while (redir)
	{

		if (redir->type != TOKEN_HEREDOC)
		{
			if (redirect(data, redir->type, redir->next))
				return (0);
		}
		redir = redir->next;
	}
	return (1);
}

void	handle_heredoc_for_cmd(t_data *data, t_cmd *cmd)
{
	char			*heredoc_file;
	int				fd;
	t_list_tokens	*rd;

	heredoc_file = NULL;
	if (herdoc_detected(cmd))
	{
		rd = cmd->list_redirectors;
		while (rd)
		{
			if (rd->type == TOKEN_HEREDOC)
			{
				heredoc_file = handle_heredoc(cmd, data, rd->next->quote_type);
				if (heredoc_file)
				{
					fd = open(heredoc_file, O_RDONLY);
					if (fd != -1)
						(dup2(fd, STDIN_FILENO), close(fd));
					free(heredoc_file);
				}
			}
			rd = rd->next;
		}
		handle_redirections_after_heredoc(data, cmd);
	}
}

