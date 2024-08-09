/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/09 04:17:03 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//The lexer is responsible for breaking down the input string into tokens 
//that can be further processed by the parser. 

#include "minishell.h"

// Function Implementations
void skip_whitespace(char **input) {
    while (**input && (**input == ' ' || **input == '\t' || **input == '\n'))
        (*input)++;
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
    char *word = NULL;

    while (**input && !isspace(**input) && **input != '|' && **input != '<' && **input != '>') {
        if (**input == '\'' || **input == '"') {
            char *quoted = collect_quoted_string(input, **input);
            if (!word) {
                word = strdup(quoted);
            } else {
                size_t new_len = len + strlen(quoted);
                char *new_word = malloc(new_len + 1);
                if (!new_word) {
                    free(quoted);
                    return NULL;  // Handle malloc failure
                }
                strcpy(new_word, word);
                strcat(new_word, quoted);
                free(word);
                word = new_word;
            }
            len += strlen(quoted);
            free(quoted);  // Free the temporary quoted string
        } else {
            len++;
            (*input)++;
        }
    }
    if (!word)
        word = strndup(start, len);  // If no quotes, just copy the word directly
    return word;
}





char *merge_quoted_sections(char *input) {
    char *result = malloc(strlen(input) + 1);
    char *res_ptr = result;
    char quote = '\0';
    bool in_quotes = false;

    if (!result)
        return NULL; // Handle malloc failure

    while (*input) {
        if (*input == '\'' || *input == '"') {
            if (!in_quotes || quote != *input) {
                quote = *input;
                in_quotes = !in_quotes;
                input++;
                continue;
            }
            if (in_quotes && *input == quote) {
                in_quotes = !in_quotes;
                input++;
                continue;
            }
        }
        *res_ptr++ = *input++;
    }
    *res_ptr = '\0'; // Null-terminate the result string
    return result;
}






t_list_tokens *create_token(t_tokens_type type, char *value) {
    t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
    if (!new_token)
        return NULL;  // Handle malloc failure

    new_token->type = type;
    new_token->value = strdup(value);  // duplicate the value string
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

void tokenize(char *input, t_list_tokens **tokens) {
    char *merged_input = merge_quoted_sections(input);
    char *current = merged_input;

    while (*current) {
        skip_whitespace(&current);

        if (*current == '|') {
            add_token(tokens, TOKEN_PIPE, "|");
            current++;
        } else if (*current == '<' && *(current + 1) == '<') {
            add_token(tokens, TOKEN_HEREDOC, "<<");
            current += 2;
        } else if (*current == '<') {
            add_token(tokens, TOKEN_REDIRECT_IN, "<");
            current++;
        } else if (*current == '>' && *(current + 1) == '>') {
            add_token(tokens, TOKEN_APPEND, ">>");
            current += 2;
        } else if (*current == '>') {
            add_token(tokens, TOKEN_REDIRECT_OUT, ">");
            current++;
        } else {
            char *word = collect_word(&current);
            add_token(tokens, TOKEN_WORD, word);
            free(word);
        }
    }

    free(merged_input);  // Free the merged input string
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

static void process_quote_string(char *string, char *new_string, void (*copy_or_count)(char *, int *, char), int *count) {
    char quote = '\0';
    int i = 0;
    int j = 0;

    while (string[i]) {
        if (string[i] == '\'' || string[i] == '\"') {
            quote = string[i++];
            while (string[i] && string[i] != quote)
                copy_or_count(new_string ? new_string + j++ : NULL, count, string[i++]);
            if (string[i])
                i++;  // Skip the closing quote
        } else {
            copy_or_count(new_string ? new_string + j++ : NULL, count, string[i++]);
        }
    }
}

void count_length(char *new_string, int *count, char c) {
    (void)new_string;
    (void)c;
    (*count)++;
}

void copy_char(char *new_string, int *count, char c) {
    (void)count;
    *new_string = c;
}

bool remove_quotes_from_string(char **string) {
    char *new_string;
    int len = 0;

    if (!*string)
        return true;

    // Count the length of the string without quotes
    process_quote_string(*string, NULL, count_length, &len);
    
    // Allocate memory for the new string
    new_string = malloc((len + 1) * sizeof(char));
    if (!new_string)
        return (perror("malloc - remove quotes from elements"), false);

    // Copy characters to new string
    new_string[len] = '\0';
    process_quote_string(*string, new_string, copy_char, NULL);

    // Replace the old string with the new one
    free(*string);
    *string = new_string;
    return true;
}



bool remove_quotes_from_tokens(t_list_tokens *tokens) {
    while (tokens) {
        if (tokens->type == TOKEN_WORD) {
            if (!remove_quotes_from_string(&tokens->value))
                return false;
        }
        tokens = tokens->next;
    }
    return true;
}

int main(void) {
    char *input;
    t_list_tokens *tokens = NULL;

    while (true) {
        // Read user input using readline
        input = readline("minishell> ");
        if (!input) {
            break; // Exit loop on EOF (Ctrl+D)
        }

        // Tokenize the input
        tokenize(input, &tokens);

        // Remove quotes from tokens
        if (!remove_quotes_from_tokens(tokens)) {
            fprintf(stderr, "Error removing quotes from tokens.\n");
            free_tokens(tokens);
            free(input);
            continue;
        }

        // Print tokens
        t_list_tokens *tmp = tokens;
        while (tmp) {
            printf("Token: %s , Type: %s\n", tmp->value, token_type_to_string(tmp->type));
            tmp = tmp->next;
        }

        // Free allocated memory
        free_tokens(tokens);
        tokens = NULL;
        free(input);

        // Add input to history
        add_history(input);
    }

    return 0;
}