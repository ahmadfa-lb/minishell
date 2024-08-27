/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:42 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/27 06:14:30 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// Function to print the token list
void print_tokens_list(t_list_tokens *tokens_list) {
    t_list_tokens *current = tokens_list;
    while (current) {
        printf("Token: type=%d, value=%s\n", current->type, current->value);
        current = current->next;
    }
}

// Function to print the command list
void print_cmd_list(t_cmd *cmd_list) {
    t_cmd *current_cmd = cmd_list;
    int cmd_index = 1;

    while (current_cmd) {
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

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    char *input;
	t_env *envp_list = init_copy_envp_to_list(envp);
    t_list_tokens *tokens = NULL;
    t_cmd *cmd_list = NULL;

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
        tokens = dollar_expansion(tokens, envp_list);  // Make sure to define or pass the `env` variable

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

        
        // Split the tokens by pipes and create command nodes
        split_tokens_by_pipe(tokens, &cmd_list);
        // free_tokens(tokens);    
        // Parse redirections for all command nodes
        parse_all_redirections(cmd_list);

        // Print the command list to check the results
        print_cmd_list(cmd_list);
        

        
        free_tokens(tokens);
        tokens = NULL;
        free(input);
         free_parser_list(cmd_list);
		cmd_list = NULL;
    }

    free_envp_list(envp_list);
    // free_tokens(tokens);
    printf("\nExiting minishell...\n");
    return 0;
}
