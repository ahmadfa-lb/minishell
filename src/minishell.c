/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:42 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/21 15:24:18 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
