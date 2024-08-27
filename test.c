// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
// /*   Updated: 2024/08/20 04:37:33 by afarachi         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// #include "libft/libft.h"
// typedef enum e_token_type
// {
// 	TOKEN_WORD,
// 	TOKEN_PIPE,
// 	TOKEN_REDIRECT_IN,
// 	TOKEN_REDIRECT_OUT,
// 	TOKEN_APPEND,
// 	TOKEN_HEREDOC,
// 	TOKEN_ERROR
// } t_tokens_type;

// typedef enum e_quote_type
// {
// 	DOUBLE_QUOTE,
// 	SINGLE_QUOTE,
// 	NO_QUOTE
// } t_quote_type;

// typedef struct s_token
// {
// 	t_tokens_type type;
// 	t_quote_type quote_type;
// 	char *value;
// 	struct s_token *next;
// } t_list_tokens;

// typedef struct s_arg
// {
// 	char *value;
// 	struct s_arg *next;
// } t_arg;

// typedef struct s_command
// {
// 	t_arg *argv; // Linked list of arguments
// 	char *input_redirect;
// 	char *output_redirect;
// 	char *append_redirect;
// 	int pipe_in;
// 	int pipe_out;
// 	struct s_command *next;
// } t_command;
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void my_echo(char *input)
{
    char *argv[256]; // Assuming a max of 256 arguments
    int argc = 0;
    bool no_newline = false;

    // Skip leading spaces
    while (*input == ' ')
    {
        input++;
    }

    // Check if the first argument is "-n"
    if (strncmp(input, "-n", 2) == 0 && (input[2] == ' ' || input[2] == '\0'))
    {
        no_newline = true;
        input += 3; // Skip "-n" and the following space
    }

    // Parse remaining arguments
    while (*input)
    {
        // Skip leading spaces between arguments
        while (*input == ' ')
            input++;

        if (*input == '\0')
            break;

        // Start of argument
        argv[argc] = input;

        // Find end of argument
        while (*input && *input != ' ')
        {
            input++;
        }

        // Null-terminate the argument
        if (*input)
        {
            *input = '\0';
            input++;
        }

        argc++;
    }

    // Print arguments
    int i = 0;
    while (i < argc)
    {
        printf("%s", argv[i]);
        i++;
        if (i < argc)
        {
            printf(" ");
        }
    }

    // Print newline unless "-n" was specified
    if (!no_newline)
    {
        printf("\n");
    }
}

// void my_echo(char *input); // Declaration of my_echo function

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell> ");

        if (input == NULL)
        {
            perror("readline");
            break;
        }

        if (*input == '\0')
        {
            free(input);
            continue;
        }

        // Add input to history
        add_history(input);

        // Check if the input starts with "echo"
        if (strncmp(input, "echo", 4) == 0 && (input[4] == ' ' || input[4] == '\0'))
        {
            // Skip the "echo " part
            char *args = input + 5; // Skip "echo " (4 characters + 1 space)
            my_echo(args);
        }
        else
        {
            // Handle other commands or input
            printf("Command not recognized: %s\n", input);
        }

        free(input);
    }

    printf("\nExiting minishell...\n");
    return 0;
}
