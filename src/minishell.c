/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:42 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/16 12:52:25 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// volatile int	signalint;

// void	interactivemode(t_data *data, char **input)
// {
// 	signal(SIGINT, interactivehandle_sigint);
// 	signal(SIGQUIT, interactivehandle_sigquit);
// 	while (1)
// 	{
// 		*input = readline(">>>");
// 		if (ft_strlen(*input) != 0 && input != NULL)
// 			break ;
// 	}
// 	(void)data;
// }

// void	noninteractivemode(t_data *data, char **input)
// {
// 	signal(SIGINT, noninteractivehandle_sigint);
// 	signal(SIGQUIT, noninteractivehandle_sigint);
// 	while (data->cmd->running == 1 && signalint != 1)
// 	{
// 		if (signalint == 1)
// 			handlesignal(data);
// 		printf("\n");
// 	}
// 	(void)*input;
// }

// int	main(int ac, char **av, char **env)
// {
// 	char	*input;
// 	t_data	data;

// 	art();
// 	using_history();
// 	while (1)
// 	{
// 		interactivemode(&data, &input);
// 		if (input == NULL)
// 		{
// 			free(input);
// 			break ;
// 		}
// 		if (ft_strlen(input) != 0)
// 			add_history(input);
// 		noninteractivemode(&data, &input);
// 		initcmd(input, env, &data);
// 		free(input);
// 	}
// 	(void)ac;
// 	(void)av;
// 	return (0);
// }

// Test the lexer
int main(void)
{
	char *input;
	t_list_tokens *tokens = NULL;

	while ((input = readline("minishell> ")) != NULL)
	{
		if (*input == '\0')
		{
			free(input);
			continue;
		}

		add_history(input);

		tokenize(input, &tokens);
		concate_nodes(&tokens);
		t_list_tokens *current_token = tokens;
		
		while (current_token)
		{
			printf("Token: %s, Value: %s, quote_type: %s\n ,space: %d\n",
				   token_type_to_string(current_token->type),
				   current_token->value,
				   quote_type_to_string(current_token->quote_type),
				   current_token->space);
			current_token = current_token->next;
		}

		free_tokens(tokens);
		tokens = NULL;
		free(input);
	}

	printf("\nExiting minishell...\n");
	return 0;
}