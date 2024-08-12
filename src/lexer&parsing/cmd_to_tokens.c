/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/12 11:19:47 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//The lexer is responsible for breaking down the input string into tokens 
//that can be further processed by the parser. 

#include "minishell.h"

char *find_quoted_string(char **input, char quote)
{
    char *start;  // b7arrek l pointer la ba3d awal quote " y3ne 3a awal 7aref mn l string
    size_t len;

	start = ++(*input);
	len = 0;
    while (**input && **input != quote)
    {
        (*input)++;
        len++;
    }
    if (**input == quote)
        (*input)++;  // b7arrek l pointer la ba3d e5er quote " 
    return ft_strndup(start, len);
}

char *collect_word(char **input)
{
    char *start;        							// Pointer to mark the start of the word
    size_t len;         							// Length of the collected word
    char *word;        							 // Pointer to store the collected word
    size_t new_len;    							// Length of the new word during concatenation
    char *new_word;    							// Pointer to store the newly concatenated word

    start = *input;    							// Initialize start pointer to the current input position
    len = 0;          							// Initialize length to 0
    word = NULL;      							// Initialize word to NULL

    while (**input && !ft_isspace(**input)    // Loop until space or special characters are found
        && **input != '|' && **input != '<' && **input != '>')
    {
        if (**input == '\'' || **input == '"')    // Check if the current character is a quote
        {
            char *quoted = find_quoted_string(input, **input);    // Find the quoted string
            if (!word)    						// If no word has been collected yet
                word = ft_strdup(quoted);   	// Duplicate the quoted string to word
            else 
            {
                new_len = len + ft_strlen(quoted);    // Calculate new length
                new_word = malloc(new_len + 1);    // Allocate memory for the new word
                if (!new_word)    				// Check if memory allocation failed
                {
                    free(quoted);   			// Free the memory for the quoted string
                    return (NULL);   			// Return NULL to indicate failure
                }
                ft_strcpy(new_word, word);    	// Copy the existing word to new_word
                ft_strcat(new_word, quoted);  	// Concatenate the quoted string to new_word
                free(word);    					// Free the old word memory
                word = new_word;    			// Update word to point to the new word
            }
            len += ft_strlen(quoted);    		// Update length
            free(quoted);    					// Free the quoted string memory
        } else
        {
            len++;    							// Increment length for each character
            (*input)++;    						// Move to the next character in the input
        }
    }
    if (!word)    								// If no word was collected
        word = ft_strndup(start, len);    		// Duplicate the substring from start to length

    return (word);    							// Return the collected word
}

char *concatenate_quoted_substrings(char *input) // Function to concatenate quoted substrings from input
{
    char *result;                              // Pointer for the final concatenated string
    char *res_ptr;                             // Pointer to traverse and build the result
    char quote;                        		   // Current quote character, initialized to no quote
    bool in_quotes;                            // Flag to track if inside a quoted section

    result = malloc(strlen(input) + 1);        // Allocate memory for the result string
	quote = '\0';
	in_quotes = false;  
    if (!result)                               // Check if memory allocation was successful
        return NULL;                           // Return NULL if allocation failed
    res_ptr = result;                          // Initialize res_ptr to the start of the result
    while (*input)                             // Loop through each character in the input
    {
        if ((*input == '\'' || *input == '"')  // Check if entering or exiting a quoted section
			&& (!in_quotes || quote == *input))
        {
            if (in_quotes && *input == quote)  // If exiting the quoted section
                in_quotes = false;             // Set in_quotes to false
            else                               // If entering a quoted section
            {
                quote = *input;                // Set the current quote character
                in_quotes = true;              // Set in_quotes to true
            }
        }
        else                                   // If the character is not a quote
            *res_ptr++ = *input;               // Copy the character to the result and move to the next position
        input++;                               // Move to the next character in the input
    }
    *res_ptr = '\0';                           // Null-terminate the result string
    return (result);                             // Return the concatenated result
}



t_list_tokens *create_token(t_tokens_type type, char *value) // Function to create a new token
{
    t_list_tokens *new_token;                                // Pointer for the new token

    new_token = malloc(sizeof(t_list_tokens));               // Allocate memory for the new token
    if (!new_token)                                          // Check if memory allocation was successful
        return NULL;                                         // Return NULL if allocation failed

    new_token->type = type;                                  // Set the token type
    new_token->value = strdup(value);                        // Duplicate and set the token value
    new_token->next = NULL;                                  // Initialize the next pointer to NULL
    return (new_token);                                      // Return the created token
}


void append_token(t_list_tokens **tokens, t_list_tokens *new_token) // Function to append a new token to the list
{
    t_list_tokens *tmp;                                          // Temporary pointer to traverse the list

    if (!*tokens)                                                // If the list is empty
        *tokens = new_token;                                     // Set the new token as the first element
    else
    {
        tmp = *tokens;                                           // Start at the beginning of the list
        while (tmp->next)                                        // Traverse to the end of the list
            tmp = tmp->next;                                     // Move to the next token in the list
        tmp->next = new_token;                                   // Append the new token at the end
    }
}


t_list_tokens *add_token(t_list_tokens **tokens,               // Function to create and add a new token to the list
    t_tokens_type type, char *value)                           
{
    t_list_tokens *new_token;                                  // Pointer for the new token

    new_token = create_token(type, value);                     // Create a new token with the given type and value
    if (!new_token)                                            // Check if token creation was successful
        return NULL;                                           // Return NULL if creation failed

    append_token(tokens, new_token);                           // Append the new token to the list of tokens
    return (new_token);                                        // Return the newly created token
}

void tokenize(char *input, t_list_tokens **tokens)              // Function to tokenize the input string
{
    char *merged_input;                                         // Pointer for the input with quoted substrings concatenated
    char *current;                                              // Pointer to traverse the merged input

    merged_input = concatenate_quoted_substrings(input);        // Concatenate quoted substrings in the input
    current = merged_input;                                     // Initialize current to the start of merged input
    while (*current)                                            // Loop through each character in the merged input
    {
        ft_skip_whitespace(&current);                           // Skip any leading whitespace
        if (*current == '|')                                    // If the current character is a pipe ('|')
        {
            add_token(tokens, TOKEN_PIPE, "|");                 // Add a pipe token to the list
            current++;                                          // Move to the next character
        } 
        else if (*current == '<' && *(current + 1) == '<')      // If the current and next characters are '<<'
        {
            add_token(tokens, TOKEN_HEREDOC, "<<");             // Add a heredoc token to the list
            current += 2;                                       // Move past the '<<'
        } 
        else if (*current == '<')                               // If the current character is a single '<'
        {
            add_token(tokens, TOKEN_REDIRECT_IN, "<");          // Add a redirect in token to the list
            current++;                                          // Move to the next character
        } 
        else if (*current == '>' && *(current + 1) == '>')     // If the current and next characters are '>>'
        {
            add_token(tokens, TOKEN_APPEND, ">>");              // Add an append token to the list
            current += 2;                                       // Move past the '>>'
        } 
        else if (*current == '>')                               // If the current character is a single '>'
        {
            add_token(tokens, TOKEN_REDIRECT_OUT, ">");         // Add a redirect out token to the list
            current++;                                          // Move to the next character
        } 
        else                                                    // If the current character is part of a word
        {
            char *word = collect_word(&current);                // Collect the word starting at current
            add_token(tokens, TOKEN_WORD, word);                // Add a word token to the list
            free(word);                                         // Free the allocated memory for the word
        }
    }
    free(merged_input);                                         // Free the memory allocated for merged_input
}

void free_tokens(t_list_tokens *tokens)                 // Function to free the memory of a linked list of tokens
{
    while (tokens)                                      // Loop through each token in the list
    {
        t_list_tokens *next = tokens->next;             // Store the next token in the list
        free(tokens->value);                            // Free the memory allocated for the token's value
        free(tokens);                                   // Free the memory allocated for the current token
        tokens = next;                                  // Move to the next token in the list
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

void handle_quoted_input(char *string, char *new_string,  // Function to handle quoted sections in the input string
    void (*copy_or_count)(char *, int *, char), int *count) // Function pointer for copying or counting characters
{
    char quote;         								// Variable to store the current quote character
    int i;                 								// Index for traversing the input string
    int j;                 								// Index for placing characters in the new_string

	quote = '\0';
	i = 0;
	j = 0;
    while (string[i])          								// Loop through each character in the input string
    {
        if (string[i] == '\'' || string[i] == '\"')  		// Check if the current character is a quote
        {
            quote = string[i++];  							// Store the quote character and move to the next character
            while (string[i] && string[i] != quote)  		// Process characters until the closing quote is found
                copy_or_count(new_string ? new_string + j++ : NULL, count, string[i++]);  // Copy or count the character
            if (string[i])  								// If there is a closing quote
                i++;  										// Move past the closing quote
        }
        else
            copy_or_count(new_string ? new_string + j++ : NULL, count, string[i++]);  // Copy or count the current character
    }
}

void count_length(char *new_string, int *count, char c)
{
    (void)new_string;
    (void)c;
    (*count)++;
}

void copy_char(char *new_string, int *count, char c)
{
    (void)count;
    *new_string = c;
}

bool remove_quotes_from_string(char **string)
{
    char *new_string;    									// Pointer to store the new string without quotes
    int len;            									// Variable to store the length of the new string

    len = 0;            									// Initialize length to 0
    if (!*string)      										// Check if the input string is NULL
        return (true); 										// Return true if there's nothing to process

    handle_quoted_input(*string, NULL, count_length, &len); // Determine the length of the new string by counting characters

    new_string = malloc((len + 1) * sizeof(char)); 			// Allocate memory for the new string, including space for the null terminator
    if (!new_string)   										// Check if memory allocation failed
        return (perror("malloc - remove quotes from elements"), false); // Print an error message and return false

    new_string[len] = '\0'; 								// Null-terminate the new string

    handle_quoted_input(*string, new_string, copy_char, NULL); // Copy characters from the input string to the new string, excluding quotes

    free(*string);    										// Free the original input string
    *string = new_string; 									// Update the original string pointer to point to the new string
    return (true);   										// Return true to indicate success
}

bool remove_quotes_from_tokens(t_list_tokens *tokens)
{
    while (tokens)  										// Iterate through the list of tokens
    {
        if (tokens->type == TOKEN_WORD)  					// Check if the current token is of type TOKEN_WORD
        {
            if (!remove_quotes_from_string(&tokens->value)) // Remove quotes from the token's value
                return (false);  							// Return false if removing quotes failed
        }
        tokens = tokens->next;  							// Move to the next token in the list
    }
    return (true);  										// Return true if all tokens were processed successfully
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
        if (input)
        {
            add_history(input);
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
