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

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ctype.h>
// #include <readline/readline.h>
// #include <readline/history.h>
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

// t_command *init_command()
// {
// 	t_command *cmd = malloc(sizeof(t_command));
// 	if (!cmd)
// 		return NULL;
// 	cmd->argv = NULL;
// 	cmd->input_redirect = NULL;
// 	cmd->output_redirect = NULL;
// 	cmd->append_redirect = NULL;
// 	cmd->pipe_in = 0;
// 	cmd->pipe_out = 0;
// 	cmd->next = NULL;
// 	return cmd;
// }

// t_arg *create_arg_node(char *value)
// {
// 	t_arg *new_arg = malloc(sizeof(t_arg));
// 	if (!new_arg)
// 		return NULL;
// 	new_arg->value = strdup(value);
// 	new_arg->next = NULL;
// 	return new_arg;
// }
// void append_arg(t_arg **argv, char *value)
// {
// 	t_arg *new_arg = create_arg_node(value);
// 	if (!new_arg)
// 		return;

// 	if (*argv == NULL)
// 	{
// 		*argv = new_arg;
// 	}
// 	else
// 	{
// 		t_arg *last = *argv;
// 		while (last->next)
// 		{
// 			last = last->next;
// 		}
// 		last->next = new_arg;
// 	}
// }

// // Helper function to append a token to the list
// static void append_token(t_list_tokens **tokens, t_list_tokens *new_token)
// {
// 	t_list_tokens *last = *tokens;
// 	if (!last)
// 	{
// 		*tokens = new_token;
// 		return;
// 	}
// 	while (last->next)
// 	{
// 		last = last->next;
// 	}
// 	last->next = new_token;
// }

// // Function to join two strings and free the old ones
// static char *strjoin_and_free(char *s1, char *s2)
// {
// 	char *result = malloc(strlen(s1) + strlen(s2) + 1);
// 	if (!result)
// 	{
// 		free(s1);
// 		free(s2);
// 		return NULL;
// 	}
// 	strcpy(result, s1);
// 	strcat(result, s2);
// 	free(s1);
// 	free(s2);
// 	return result;
// }

// char *ft_strncpy(char *dest, const char *src, size_t n)
// {
// 	size_t i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		if (src[i] != '\0')
// 			dest[i] = src[i];
// 		else
// 			dest[i] = '\0';
// 		i++;
// 	}
// 	return (dest);
// }

// char *ft_strcpy(char *dest, const char *src)
// {
// 	char *dest_ptr;

// 	dest_ptr = dest;
// 	while (*src)
// 		*dest_ptr++ = *src++;
// 	*dest_ptr = '\0';
// 	return (dest);
// }

// char *ft_strcat(char *dest, const char *src)
// {
// 	char *dest_ptr;

// 	dest_ptr = dest;
// 	while (*dest_ptr)
// 		dest_ptr++;
// 	while (*src)
// 		*dest_ptr++ = *src++;
// 	*dest_ptr = '\0';
// 	return (dest);
// }

// size_t ft_strnlen(const char *str, size_t n)
// {
// 	size_t length;

// 	length = 0;
// 	while (length < n && str[length] != '\0')
// 		length++;
// 	return (length);
// }

// char *ft_strndup(const char *s, size_t n)
// {
// 	size_t len = ft_strnlen(s, n);
// 	char *new_str = malloc(len + 1);
// 	if (!new_str)
// 		return NULL;
// 	ft_strncpy(new_str, s, len);
// 	new_str[len] = '\0';
// 	return new_str;
// }

// // Function to process quoted strings
// static char *process_quoted_string(char **input, char quote_type)
// {
// 	char *start = ++(*input); // Skip the opening quote
// 	char *end;
// 	char *result;
// 	size_t len;

// 	while (**input && **input != quote_type)
// 	{
// 		if (**input == '\\' && (*(*input + 1) == quote_type || *(*input + 1) == '\\'))
// 		{
// 			(*input)++; // Skip escaped character
// 		}
// 		(*input)++;
// 	}

// 	end = *input;
// 	// if (**input == quote_type)
// 	// {
// 	// 	(*input)++; // Skip closing quote
// 	// }

// 	len = end - start;
// 	result = malloc(len + 1);
// 	if (!result)
// 		return NULL;
// 	ft_strncpy(result, start, len);
// 	result[len] = '\0';

// 	return result;
// }

// // Tokenize the input string into tokens
// void tokenize(char *input, t_list_tokens **tokens)
// {
// 	char *current = input;
// 	char *start;
// 	t_list_tokens *last_token = NULL;
// 	char quote_type = NO_QUOTE;

// 	while (*current)
// 	{
// 		// Skip whitespace
// 		while (ft_isspace(*current))
// 			current++;

// 		// Handle pipes
// 		if (*current == '|')
// 		{
// 			t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
// 			if (!new_token)
// 				return;

// 			new_token->type = TOKEN_PIPE;
// 			new_token->value = ft_strdup("|");
// 			new_token->quote_type = NO_QUOTE;
// 			new_token->next = NULL;

// 			append_token(tokens, new_token);
// 			last_token = new_token;
// 			current++;
// 			continue;
// 		}

// 		// Handle redirections
// 		if (*current == '<' || *current == '>')
// 		{
// 			char redirect_char = *current;
// 			size_t len = 1;
// 			if (*(current + 1) == redirect_char)
// 			{
// 				len++;
// 				current++;
// 			}

// 			t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
// 			if (!new_token)
// 				return;

// 			new_token->type = (redirect_char == '<') ? TOKEN_REDIRECT_IN : TOKEN_REDIRECT_OUT;
// 			if (len == 2)
// 				new_token->type = (redirect_char == '<') ? TOKEN_HEREDOC : TOKEN_APPEND;

// 			new_token->value = ft_strndup(current - len + 1, len);
// 			new_token->quote_type = NO_QUOTE;
// 			new_token->next = NULL;

// 			append_token(tokens, new_token);
// 			last_token = new_token;
// 			current++;
// 			continue;
// 		}

// 		// Handle quoted strings
// 		if (*current == '"' || *current == '\'')
// 		{
// 			quote_type = *current;
// 			char *quoted_string = process_quoted_string(&current, quote_type);
// 			if (!quoted_string)
// 				return;

// 			t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
// 			if (!new_token)
// 			{
// 				free(quoted_string);
// 				return;
// 			}

// 			new_token->type = TOKEN_WORD;
// 			new_token->value = quoted_string;
// 			new_token->quote_type = (quote_type == '"') ? DOUBLE_QUOTE : SINGLE_QUOTE;
// 			new_token->next = NULL;

// 			append_token(tokens, new_token);
// 			last_token = new_token;
// 			current++;
// 			continue;
// 		}

// 		// Handle unquoted words
// 		start = current;
// 		while (*current && !ft_isspace(*current) && *current != '|' &&
// 			   *current != '<' && *current != '>' && *current != '"' && *current != '\'')
// 		{
// 			current++;
// 		}

// 		if (current > start)
// 		{
// 			t_list_tokens *new_token = malloc(sizeof(t_list_tokens));
// 			if (!new_token)
// 				return;

// 			new_token->type = TOKEN_WORD;
// 			new_token->value = ft_strndup(start, current - start);
// 			new_token->quote_type = NO_QUOTE;
// 			new_token->next = NULL;

// 			// if (last_token && last_token->type == TOKEN_WORD)
// 			// {
// 			// 	last_token->value = strjoin_and_free(last_token->value, new_token->value);
// 			// 	free(new_token);
// 			// }
// 			// else
// 			// {
// 			append_token(tokens, new_token);
// 			last_token = new_token;
// 			// }
// 		}
// 	}
// }
// t_command *parse_tokens(t_list_tokens *tokens)
// {
// 	t_command *cmd = init_command();
// 	t_command *head = cmd;
// 	t_list_tokens *current_token = tokens;

// 	while (current_token)
// 	{
// 		if (current_token->type == TOKEN_WORD)
// 		{
// 			append_arg(&cmd->argv, current_token->value);
// 		}
// 		else if (current_token->type == TOKEN_PIPE)
// 		{
// 			cmd->pipe_out = 1;
// 			t_command *new_cmd = init_command();
// 			new_cmd->pipe_in = 1;
// 			cmd->next = new_cmd;
// 			cmd = new_cmd;
// 		}
// 		else if (current_token->type == TOKEN_REDIRECT_IN)
// 		{
// 			current_token = current_token->next;
// 			if (current_token && current_token->type == TOKEN_WORD)
// 				cmd->input_redirect = strdup(current_token->value);
// 			else
// 				fprintf(stderr, "Syntax error: expected a file after '<'\n");
// 		}
// 		else if (current_token->type == TOKEN_REDIRECT_OUT)
// 		{
// 			current_token = current_token->next;
// 			if (current_token && current_token->type == TOKEN_WORD)
// 				cmd->output_redirect = strdup(current_token->value);
// 			else
// 				fprintf(stderr, "Syntax error: expected a file after '>'\n");
// 		}
// 		else if (current_token->type == TOKEN_APPEND)
// 		{
// 			current_token = current_token->next;
// 			if (current_token && current_token->type == TOKEN_WORD)
// 				cmd->append_redirect = strdup(current_token->value);
// 			else
// 				fprintf(stderr, "Syntax error: expected a file after '>>'\n");
// 		}
// 		else
// 		{
// 			fprintf(stderr, "Syntax error: unexpected token '%s'\n", current_token->value);
// 		}

// 		// Handle other token types (redirections, etc.) here...

// 		current_token = current_token->next;
// 	}

// 	return head;
// }

// // Free the token list
// void free_tokens(t_list_tokens *tokens)
// {
// 	while (tokens)
// 	{
// 		t_list_tokens *next = tokens->next;
// 		free(tokens->value);
// 		free(tokens);
// 		tokens = next;
// 	}
// }

// // Convert token type to string
// const char *token_type_to_string(t_tokens_type type)
// {
// 	switch (type)
// 	{
// 	case TOKEN_WORD:
// 		return "TOKEN_WORD";
// 	case TOKEN_PIPE:
// 		return "TOKEN_PIPE";
// 	case TOKEN_REDIRECT_IN:
// 		return "TOKEN_REDIRECT_IN";
// 	case TOKEN_REDIRECT_OUT:
// 		return "TOKEN_REDIRECT_OUT";
// 	case TOKEN_APPEND:
// 		return "TOKEN_APPEND";
// 	case TOKEN_HEREDOC:
// 		return "TOKEN_HEREDOC";
// 	case TOKEN_ERROR:
// 		return "TOKEN_ERROR";
// 	default:
// 		return "UNKNOWN";
// 	}
// }

// const char *quote_type_to_string(t_quote_type quote_type)
// {
// 	switch (quote_type)
// 	{
// 	case DOUBLE_QUOTE:
// 		return "DOUBLE_QUOTE";
// 	case SINGLE_QUOTE:
// 		return "SINGLE_QUOTE";
// 	default:
// 		return "NO_QUOTE";
// 	}
// }
// void print_parsed_tokens(t_command *commands)
// {
// 	t_command *cmd = commands;

// 	while (cmd)
// 	{
// 		printf("Command:\n");

// 		// Print arguments as a linked list
// 		if (cmd->argv)
// 		{
// 			printf("  Arguments: ");
// 			t_arg *arg = cmd->argv;
// 			while (arg)
// 			{
// 				printf("%s ", arg->value);
// 				arg = arg->next;
// 			}
// 			printf("\n");
// 		}

// 		// Print input redirection
// 		if (cmd->input_redirect)
// 		{
// 			printf("  Input Redirect: %s\n", cmd->input_redirect);
// 		}

// 		// Print output redirection
// 		if (cmd->output_redirect)
// 		{
// 			printf("  Output Redirect: %s\n", cmd->output_redirect);
// 		}

// 		// Print append redirection
// 		if (cmd->append_redirect)
// 		{
// 			printf("  Append Redirect: %s\n", cmd->append_redirect);
// 		}

// 		// Print pipe status
// 		if (cmd->pipe_in)
// 		{
// 			printf("  Pipe In: True\n");
// 		}
// 		if (cmd->pipe_out)
// 		{
// 			printf("  Pipe Out: True\n");
// 		}

// 		printf("\n");

// 		// Move to the next command in the pipeline
// 		cmd = cmd->next;
// 	}
// }

// void free_argv(t_arg *argv)
// {
// 	while (argv)
// 	{
// 		t_arg *next = argv->next;
// 		free(argv->value);
// 		free(argv);
// 		argv = next;
// 	}
// }

// int main(void)
// {
// 	char *input;
// 	t_list_tokens *tokens = NULL;
// 	t_command *commands = NULL;

// 	while ((input = readline("minishell> ")) != NULL)
// 	{
// 		if (*input == '\0')
// 		{
// 			free(input);
// 			continue;
// 		}

// 		add_history(input);
// 		tokenize(input, &tokens);

// 		// Print the parsed tokens
// 		t_list_tokens *current_token = tokens;
// 		while (current_token)
// 		{
// 			printf("Token: %s, Value: %s, quote_type: %s\n",
// 				   token_type_to_string(current_token->type),
// 				   current_token->value,
// 				   quote_type_to_string(current_token->quote_type));
// 			current_token = current_token->next;
// 		}
// 		commands = parse_tokens(tokens);
// 		print_parsed_tokens(commands);

// 		// Execute commands here...

// 		free_tokens(tokens);
// 		// Free commands here...
// 		tokens = NULL;
// 		free(input);
// 	}

// 	printf("\nExiting minishell...\n");
// 	return 0;
// }