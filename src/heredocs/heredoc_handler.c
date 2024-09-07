/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:55:56 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 19:07:37 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*generate_heredoc_filename(char **delimiters, t_data *data,
	t_quote_type quote_type, int i)
{
	t_list_tokens	*heredoc_tokens;
	t_list_tokens	*temp;
	char			*filename;
	char			*file_num;
	int				fd;

	heredoc_tokens = NULL;
	file_num = ft_itoa(i);
	filename = ft_strjoin(ft_strdup("/tmp/heredoc_tmp.txt_"), file_num);
	heredoc_tokens = parse_input_to_tokens(delimiters[i]);
	update_heredoc_data(&heredoc_tokens, data, quote_type);
	temp = heredoc_tokens;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ((free(filename), free(file_num)), NULL);
	while (temp)
	{
		ft_putstr_fd(temp->value, fd);
		temp = temp->next;
	}
	return (free_tokens(heredoc_tokens), close(fd), free(file_num), filename);
}

char	**get_delimiters(t_list_tokens *redirectors)
{
	int		i;
	int		del_count;
	char	**result;

	del_count = get_delimiters_count(redirectors);
	result = (char **)malloc(sizeof(char *) * (del_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (redirectors)
	{
		if (redirectors->type == TOKEN_HEREDOC)
		{
			result[i] = ft_strdup(redirectors->next->value);
			i++;
		}
		redirectors = redirectors->next;
	}
	result[i] = NULL;
	return (result);
}

char	*handle_heredoc(t_cmd *cmd, t_data *data, int quote_type)
{
	char	*filename;
	char	**delimiters;
	int		delimiters_count;
	int		i;

	delimiters_count = get_delimiters_count(cmd->list_redirectors);
	delimiters = get_delimiters(cmd->list_redirectors);
	i = 0;
	filename = ft_strdup("");
	signal(SIGQUIT, handle_execution_mode);
	signal(SIGQUIT, SIG_IGN);
	while (i < delimiters_count)
	{
		reset_heredoc_signals();
		filename = generate_heredoc_filename(delimiters, data, quote_type, i);
		if (i < delimiters_count - 1)
			free(filename);
		i++;
	}
	return (free_args(delimiters), filename);
}
