/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:42 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/21 14:54:25 by afarachi         ###   ########.fr       */
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


// t_list_tokens *expand_dollar_sign(t_list_tokens *lexer_list, t_envp_node *envp_list) {
//     t_list_tokens *current = lexer_list;

//     while (current) {
//         // Check if the token value starts with '$'
//         if (current->value && current->value[0] == '$') {
//             char *env_value = get_env(envp_list, current->value + 1); // Skip the '$' character

//             if (env_value) {
//                 // Replace the current token value with the environment variable's value
//                 free(current->value);
//                 current->value = strdup(env_value);
//             } else {
//                 // If the environment variable doesn't exist, replace it with an empty string
//                 free(current->value);
//                 current->value = strdup("");
//             }
//         }

//         // Move to the next token
//         current = current->next;
//     }

//     return lexer_list;
// }

// int main(int argc, char **argv, char **envp) {
//     // Initialize envp list
//     t_envp_node *envp_list = copy_envp_to_list(envp);

//     // Sample lexer output (you would replace this with actual lexer processing)
//     t_list_tokens *lexer_list = create_lexer_list_from_input("ls -l $HOME");

//     // Before expansion
//     printf("Before expansion:\n");
//     print_lexer_list(lexer_list); // You can write a helper function to print the list

//     // Parse and expand $ sign
//     lexer_list = expand_dollar_sign(lexer_list, envp_list);

//     // After expansion
//     printf("\nAfter expansion:\n");
//     print_lexer_list(lexer_list);

//     // Cleanup
//     free_envp_list(envp_list);
//     free_lexer_list(lexer_list);

//     return 0;
// }

// Test the lexer
// int main(void)
// {
// 	char *input;
// 	t_list_tokens *tokens = NULL;

// 	while ((input = readline("minishell> ")) != NULL)
// 	{
// 		if (*input == '\0')
// 		{
// 			free(input);
// 			continue;
// 		}

// 		add_history(input);

// 		tokenize(input, &tokens);
// 		concate_nodes(&tokens);
// 		t_list_tokens *current_token = tokens;
		
// 		while (current_token)
// 		{
// 			printf("Token: %s, Value: %s, quote_type: %s\n ,space: %d\n",
// 				   token_type_to_string(current_token->type),
// 				   current_token->value,
// 				   quote_type_to_string(current_token->quote_type),
// 				   current_token->space);
// 			current_token = current_token->next;
// 		}

// 		free_tokens(tokens);
// 		tokens = NULL;
// 		free(input);
// 	}

// 	printf("\nExiting minishell...\n");
// 	return 0;
// }

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    char *input;
	t_env *envp_list = init_copy_envp_to_list(envp);
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

        // Apply dollar expansion before concatenating nodes
        dollar_expansion(tokens, envp_list);  // Make sure to define or pass the `env` variable

        concate_nodes(&tokens);

        t_list_tokens *current_token = tokens;
        while (current_token)
        {
            printf("Token: %s, Value: %s, quote_type: %s, space: %d\n",
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
