/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler_helpers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:29:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 08:52:31 by afarachi         ###   ########.fr       */
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
		line = readline("");
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
