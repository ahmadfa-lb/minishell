/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:42 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/02 16:35:38 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Function to print the token list
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




// t_data *initialize_data(void)
// {
//     t_data *data;

//     // Allocate memory for the t_data structure
//     data = (t_data *)malloc(sizeof(t_data));
//     if (!data)
//         return (NULL); // Return NULL if memory allocation fails

//     // Initialize the cmd pointer to NULL
//     data->cmd_list = NULL;
//     data->first_tokens_list = NULL;

//     // Initialize the env pointer to NULL
//     data->env_list = NULL;
//     data->env_array = NULL;

//     // Initialize the exit_status to 0 (default success status)
//     data->exit_status = 0;

//     // Initialize user_input to NULL
//     data->user_input = NULL;

//     return data;
// }

// int main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
//     //signal_number = 0;
//     t_data *data = ft_calloc(1, sizeof(t_data));
//     char *input;
// 	data->env_list = init_copy_envp_to_list(envp);
//     //t_list_tokens *tokens = NULL;
//     // t_cmd *cmd_list = NULL;

//     while ((input = readline("minishell> ")) != NULL)
//     {
//         if (*input == '\0')
//         {
//             free(input);
//             continue;
//         }

//         add_history(input);

//         tokenize(input, &data->first_tokens_list);

//         // Apply dollar expansion before concatenating nodes
//         data->first_tokens_list = dollar_expansion(data->first_tokens_list, data->env_list);  // Make sure to define or pass the `env` variable

//         concate_nodes(&data->first_tokens_list);

//         t_list_tokens *current_token = data->first_tokens_list;
//         while (current_token)
//         {
//             printf("Token: %s, Value: %s, quote_type: %s, space: %d\n",
//                    token_type_to_string(current_token->type),
//                    current_token->value,
//                    quote_type_to_string(current_token->quote_type),
//                    current_token->space);
//             current_token = current_token->next;
//         }

//         // Split the tokens by pipes and create command nodes
//         split_tokens_by_pipe(data->first_tokens_list, &data->cmd_list);
//         //free_tokens(data->first_tokens_list);
//         // Parse redirections for all command nodes
//         parse_all_redirections(data->cmd_list);

//         // Print the command list to check the results
//         print_cmd_list(data->cmd_list);

//         //ft_execute_command(data);

//         free_tokens(data->first_tokens_list);
//         data->first_tokens_list = NULL;
//         free(input);
//         //free_parser_list(data->cmd);
// 		//data->cmd = NULL;
//         //free(data);
//     }

//     free_envp_list(data->env_list);
//     // free_tokens(tokens);
//     printf("\nExiting minishell...\n");
//     return 0;
// }


int main(int argc, char **argv, char **envp)
{
    art();
    (void)argc;
    (void)argv;
    //char *input;
    t_data *data = ft_calloc(1, sizeof(t_data));
    // t_env *envp_list = init_copy_envp_to_list(envp);
    data->env_list = init_copy_envp_to_list(envp);
    // t_list_tokens *tokens = NULL;
    // t_cmd *cmd_list = NULL;

    while (1)
    {
        //free(data->env_array);
        
        data->user_input = readline("minishell> ");
        if (!data->user_input)
        {
            free(data->user_input);
            // continue;
            exit(0);
        }
        
        add_history(data->user_input);

        tokenize(data->user_input, &data->first_tokens_list);

        // Apply dollar expansion before concatenating nodes
        data->first_tokens_list = dollar_expansion(data); // Make sure to define or pass the env variable
        concate_nodes(&data->first_tokens_list);

        // t_list_tokens *current_token = data->first_tokens_list;
        // while (current_token)
        // {
        //     printf("Token: %s, Value: %s, quote_type: %s, space: %d\n",
        //            token_type_to_string(current_token->type),
        //            current_token->value,
        //            quote_type_to_string(current_token->quote_type),
        //            current_token->space);
        //     current_token = current_token->next;
        // }

        // Split the tokens by pipes and create command nodes
        split_tokens_by_pipe(data, &data->cmd_list);
        //printf("\nnb_pipes: %d\n",data->nb_pipes);
        // free_tokens(tokens);
        // Parse redirections for all command nodes
        parse_all_redirections(data->cmd_list);

        // Print the command list to check the results
        data->env_array = env_list_to_array(data);
        // print_cmd_list(data->cmd_list);
        data->exit_status =  ft_execute_command(data, data->cmd_list);
        
        free_tokens(data->first_tokens_list);
        data->first_tokens_list = NULL;
        free(data->user_input);
        free_parser_list(data->cmd_list);
        data->cmd_list = NULL;
    }
    printf("\nexit status: %d \n", data->exit_status);
    free_envp_list(data->env_list);
    free(data->env_array);
    // free_tokens(tokens);
    // printf("\n\n");
    return 0;
}