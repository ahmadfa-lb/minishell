/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/08 15:20:33 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//The lexer is responsible for breaking down the input string into tokens 
//that can be further processed by the parser. 

#include "minishell.h"

// t_list_tokens *add_token(t_list_tokens **tokens, t_tokens_type type, char *value)
// {
//     t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
//     new_token->type = type;
//     new_token->value = value;
//     new_token->next = NULL;

//     if (*tokens == NULL)
//         *tokens = new_token;
// 	else
// 	{
//         t_list_tokens *tmp = *tokens;
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = new_token;
//     }
//     return (new_token);
// }

// char *collect_word(char **input)
// {
//     char *start = *input;
//     size_t len = 0;

//     while (**input && !ft_iswhitespace(**input) && **input != '|'
// 		&& **input != '<' && **input != '>')
// 	{
//         if (**input == '\'' || **input == '"')
//         {
//             char quote = *(*input)++;
//             while (**input && **input != quote)
//                 (*input)++;
//             if (**input == quote)
//                 (*input)++;
//         } else
//             (*input)++;
//         len++;
//     }
//     return (strndup(start, len));
// }

// // Tokenizer function
// int *tokenize(char *input, t_list_tokens *tokens)
// {
//     while (*input)
//     {
//         while (ft_iswhitespace(*input))
// 			input++;
//         if (*input == '|')
//         {
//             add_token(&tokens, TOKEN_PIPE, "|");
//             input++;
//         } 
//         else if (*input == '<' && *(input + 1) == '<')
//         {
//             add_token(&tokens, TOKEN_HEREDOC, "<<");
//             input += 2;
//         }
//         else if (*input == '<') {
//             add_token(&tokens, TOKEN_REDIRECT_IN, "<");
//             input++;
//         }
//         else if (*input == '>' && *(input + 1) == '>')
//         {
//             add_token(&tokens, TOKEN_APPEND, ">>");
//             input += 2;
//         }
//         else if (*input == '>')
//         {
//             add_token(&tokens, TOKEN_REDIRECT_OUT, ">");
//             input++;
//         } 
//         else
//         {
//             char *word = collect_word(&input);
//             add_token(&tokens, TOKEN_WORD, word);
//             free(word);
//         }
//     }
//     return tokens;
// }

// void free_tokens(t_list_tokens *tokens)
// {
//     while (tokens)
//     {
//         t_list_tokens *next = tokens->next;
//         free(tokens->value);
//         free(tokens);
//         tokens = next;
//     }
// }


t_list_tokens *create_token(t_tokens_type type, char *value) {
    t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
    if (!new_token)
        return NULL;  // Handle malloc failure

    new_token->type = type;  // type should be a string
    new_token->value = strdup(value); // duplicate the value string
    new_token->next = NULL;
    return new_token;
}


void append_token(t_list_tokens **tokens, t_list_tokens *new_token) {
    if (!*tokens) {
        *tokens = new_token;
    } else {
        t_list_tokens *tmp = *tokens;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_token;
    }
}

t_list_tokens *add_token(t_list_tokens **tokens, t_tokens_type type, char *value) {
    t_list_tokens *new_token = create_token(type, value);
    if (!new_token)
        return NULL;  // Handle token creation failure

    append_token(tokens, new_token);
    return new_token;
}

char *collect_quoted_string(char **input, char quote) {
    char *start = ++(*input);  // Move past the opening quote
    size_t len = 0;

    while (**input && **input != quote) {
        (*input)++;
        len++;
    }
    if (**input == quote)
        (*input)++;  // Move past the closing quote

    return strndup(start, len);
}

char *collect_word(char **input) {
    char *start = *input;
    size_t len = 0;

    while (**input && !ft_iswhitespace(**input) && **input != '|' && **input != '<' && **input != '>') {
        if (**input == '\'' || **input == '"') {
            char *quoted = collect_quoted_string(input, **input);
            len += strlen(quoted);
            free(quoted);  // Free the temporary quoted string
        } else {
            (*input)++;
            len++;
        }
    }
    return strndup(start, len);
}

void skip_whitespace(char **input) {
    while (ft_iswhitespace(**input))
        (*input)++;
}

void tokenize(char *input, t_list_tokens **tokens) {
    while (*input) {
        skip_whitespace(&input);

        if (*input == '|') {
            add_token(tokens, TOKEN_PIPE, "|");
            input++;
        } else if (*input == '<' && *(input + 1) == '<') {
            add_token(tokens, TOKEN_HEREDOC, "<<");
            input += 2;
        } else if (*input == '<') {
            add_token(tokens, TOKEN_REDIRECT_IN, "<");
            input++;
        } else if (*input == '>' && *(input + 1) == '>') {
            add_token(tokens, TOKEN_APPEND, ">>");
            input += 2;
        } else if (*input == '>') {
            add_token(tokens, TOKEN_REDIRECT_OUT, ">");
            input++;
        } else {
            char *word = collect_word(&input);
            add_token(tokens, TOKEN_WORD, word);
            free(word);
        }
    }
}

void free_tokens(t_list_tokens *tokens) {
    while (tokens) {
        t_list_tokens *next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}


const char *token_type_to_string(t_tokens_type type) {
    switch (type) {
        case TOKEN_WORD:          return "TOKEN_WORD";
        case TOKEN_PIPE:          return "TOKEN_PIPE";
        case TOKEN_REDIRECT_IN:   return "TOKEN_REDIRECT_IN";
        case TOKEN_REDIRECT_OUT:  return "TOKEN_REDIRECT_OUT";
        case TOKEN_APPEND:        return "TOKEN_APPEND";
        case TOKEN_HEREDOC:       return "TOKEN_HEREDOC";
        case TOKEN_ERROR:         return "TOKEN_ERROR";
        case TOKEN_FILENAME:      return "TOKEN_FILENAME";
        default:                  return "UNKNOWN";
    }
}

int main(void) {
    t_list_tokens *tokens = NULL;
    char *input;

    while ((input = readline("minishell> ")) != NULL) {
        if (*input != '\0') {
            add_history(input);
            tokenize(input, &tokens);

            // Print the tokens to verify
            t_list_tokens *tmp = tokens;
            while (tmp) {
                printf("Type: %s, Value: %s\n", token_type_to_string(tmp->type), tmp->value);
                tmp = tmp->next;
            }

            // Free the token list
            free_tokens(tokens);
            tokens = NULL;  // Reset the token list for the next input
        }
        free(input);  // Free the input string
    }

    return 0;
}