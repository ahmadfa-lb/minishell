/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:44:32 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 06:59:41 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/minishell.h"

char *strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    char *new_str = malloc(len + 1); // Allocate memory for the new string
    if (!new_str) return NULL;       // Check for allocation failure
    strncpy(new_str, s, len);        // Copy the substring
    new_str[len] = '\0';             // Null-terminate the new string
    return new_str;
}

t_list_tokens *add_token(t_list_tokens **tokens, t_list_tokens_type type, char *value) {
    t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
    new_token->type = type;
    new_token->value = value;
    new_token->next = NULL;

    if (*tokens == NULL) {
        *tokens = new_token;
    } else {
        t_list_tokens *tmp = *tokens;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_token;
    }
    return (new_token);
}

char *collect_word(char **input) {
    char *start = *input;
    size_t len = 0;

    while (**input && !isspace(**input) && **input != '|' && **input != '<' && **input != '>') {
        if (**input == '\'' || **input == '"') {
            char quote = *(*input)++;
            while (**input && **input != quote)
                (*input)++;
            if (**input == quote)
                (*input)++;
        } else {
            (*input)++;
        }
        len++;
    }

    return strndup(start, len);
}

// Tokenizer function
t_list_tokens *tokenize(char *input) {
    t_list_tokens *tokens = NULL;

    while (*input) {
        while (isspace(*input)) input++;  // Skip whitespace

        if (*input == '|') {
            add_token(&tokens, TOKEN_PIPE, "|");
            input++;
        } else if (*input == '<' && *(input + 1) == '<') {
            add_token(&tokens, TOKEN_HEREDOC, "<<");
            input += 2;
        } else if (*input == '<') {
            add_token(&tokens, TOKEN_REDIRECT_IN, "<");
            input++;
        } else if (*input == '>' && *(input + 1) == '>') {
            add_token(&tokens, TOKEN_APPEND, ">>");
            input += 2;
        } else if (*input == '>') {
            add_token(&tokens, TOKEN_REDIRECT_OUT, ">");
            input++;
        } else {
            char *word = collect_word(&input);
            add_token(&tokens, TOKEN_WORD, word);
            free(word);
        }
    }

    add_token(&tokens, TOKEN_EOF, NULL);  // End of input
    return tokens;
}

// char	*find_path(char **envp)
// {
// 	while (ft_strncmp("PATH", *envp, 4))
// 		envp++;
// 	return (*envp + 5);
// }

void free_tokens(t_list_tokens *tokens) {
    while (tokens) {
        t_list_tokens *next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}

int main(int argc, char *argv[])
{
	char *tokens_[] = 
	{
		"TOKEN_WORD",
		"TOKEN_PIPE",
		"TOKEN_REDIRECT_IN",
		"TOKEN_REDIRECT_OUT",
		"TOKEN_APPEND",
		"TOKEN_HEREDOC",
		"TOKEN_ERROR",
		"TOKEN_EOF"
	};
	t_list_tokens *tokens;

	tokens = tokenize(argv[1]);
	while (tokens)
	{
		printf("%s\t %s\n", tokens_[tokens->type], tokens->value);
		tokens = tokens->next;
	}
	free_tokens(tokens);
    return 0;
}
