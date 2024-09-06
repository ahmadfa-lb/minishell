/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabbas <moabbas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:42 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 20:26:06 by moabbas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	return (str[i] == '\0');
}

// Convert token type to string
const char *token_type_to_string(t_tokens_type type)
{
	switch (type)
	{
	case TOKEN_WORD:
		return "TOKEN_WORD";
	case TOKEN_PIPE:
		return "TOKEN_PIPE";
	case TOKEN_REDIRECT_IN:
		return "TOKEN_REDIRECT_IN";
	case TOKEN_REDIRECT_OUT:
		return "TOKEN_REDIRECT_OUT";
	case TOKEN_APPEND:
		return "TOKEN_APPEND";
	case TOKEN_HEREDOC:
		return "TOKEN_HEREDOC";
	case TOKEN_ERROR:
		return "TOKEN_ERROR";
	default:
		return "UNKNOWN";
	}
}

const char *quote_type_to_string(t_quote_type quote_type)
{
	switch (quote_type)
	{
	case DOUBLE_QUOTE:
		return "DOUBLE_QUOTE";
	case SINGLE_QUOTE:
		return "SINGLE_QUOTE";
	default:
		return "NO_QUOTE";
	}
}


void print_tokens_list(t_list_tokens *tokens_list)
{
    t_list_tokens *current = tokens_list;
    while (current)
    {
        printf("Token: type=%d, value=%s\n", current->type, current->value);
        current = current->next;
    }
}

// Function to print the command list
void print_cmd_list(t_cmd *cmd_list)
{
    t_cmd *current_cmd = cmd_list;
    int cmd_index = 1;

    while (current_cmd)
    {
        printf("Command Node %d:\n", cmd_index);
        printf("Tokens List:\n");
        print_tokens_list(current_cmd->tokens_list);
        printf("Redirectors List:\n");
        print_tokens_list(current_cmd->list_redirectors);
        printf("\n");

        current_cmd = current_cmd->next;
        cmd_index++;
    }
}


int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(art(), (void)argc, (void)argv);
	data = ft_calloc(1, sizeof(t_data));
	data->env_list = init_copy_envp_to_list(envp);
	setup_initial_environment(&data->env_list);
	// set_signals();
	while (1)
	{
		data->user_input = readline("minishell> ");
		handle_ctrl_d(data);
		update_exit_status_on_signal(&data->exit_status);
		if (!is_white_space(data->user_input))
			add_history(data->user_input);
		tokenize(data->user_input, &data->first_tokens_list);
		data->first_tokens_list
		 	= dollar_expansion(data->first_tokens_list, data);
		concate_nodes(&data->first_tokens_list);
		if (check_initial_errors(data->user_input, data))
		{
			split_tokens_by_pipe(data, &data->cmd_list);
			parse_all_redirections(data->cmd_list);
			data->env_array = env_list_to_array(data);
			data->exit_status = ft_execute_command(data, data->cmd_list);
			free_args(data->env_array);
		}
		(free_tokens(data->first_tokens_list), free(data->user_input));
		(free_parser_list(data->cmd_list), data->cmd_list = NULL);
		data->first_tokens_list = NULL;
	}
	rl_clear_history();
	return (free_envp_list(data->env_list), free(data->env_array), 0);
}
