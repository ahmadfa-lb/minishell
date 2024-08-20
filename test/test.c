/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 02:36:24 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/20 16:26:10 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include "./ft_libft/libft.h"
#include <stdint.h>
#include <fcntl.h>

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
} t_env;

char *ft_strcopy(char *dest, const char *src)
{
	size_t i;

	i = 0;
	while (src[i])
	{
		if (src[i] != '\0')
			dest[i] = src[i];
		else
			dest[i] = '\0';
		i++;
	}
	return (dest);
}

int ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r');
}

t_env *create_node(char *key, char *value)
{
	t_env *res;
	int i;

	res = malloc(sizeof(t_env));
	i = 0;
	if (!res)
	{
		perror("Failed to allocate memory for new node");
		return (NULL);
	}
	res->key = ft_strdup(key);
	res->value = ft_strdup(value); // Initialize value_head to NULL
	res->next = NULL;
	return (res);
}

void append_node(t_env **head, char *key, char *value)
{
	t_env *new_node;
	t_env *current;

	new_node = create_node(key, value);
	if (!new_node)
		return;
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}

void free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
// free functions
void free_list(t_env *env_head)
{
	t_env *current_env;
	t_env *next_env;

	current_env = env_head;
	while (current_env)
	{
		next_env = current_env->next;
		// Free the key
		free(current_env->key);
		// Free the value list associated with this env node
		free(current_env->value);
		// Free the env node itself
		free(current_env);
		current_env = next_env;
	}
}

void init_copy_envp(t_env **head, char **envp)
{
	char **copy_env;
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		copy_env = ft_split(envp[i], '=');
		if (copy_env)
		{
			if (copy_env[0] && copy_env[1])
				append_node(head, copy_env[0], copy_env[1]);
			else if (copy_env[0] && !copy_env[1])
				append_node(head, copy_env[0], ft_strdup(""));
			free_tab(copy_env);
		}
		i++;
	}
}
// for testing

void print_list(t_env *env_head)
{
	t_env *current_env;
	char *current_value;

	current_env = env_head;
	while (current_env)
	{
		// Print the key
		printf("Key: %s\n", current_env->key);
		// Print the values
		current_value = current_env->value;
		printf("Values: ");
		printf("%s", current_value);
		printf("\n\n"); // Print a newline between entries
		// Move to the next env node
		current_env = current_env->next;
	}
}

// int count_envp_elements(char **envp)
// {
// 	int count = 0;
// 	while (envp[count] != NULL)
// 	{
// 		count++;
// 	}
// 	return (count);
// }

// int list_length(t_env *head)
// {
// 	int length = 0;
// 	t_env *current = head;
// 	while (current)
// 	{
// 		length++;
// 		current = current->next;
// 	}
// 	return (length);
// }

char *my_getenv_from_copy(char *name, t_env *copy_envp)
{
	t_env *current = copy_envp;

	// Traverse the linked list to find the matching key
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
		{
			// Found the matching key, concatenate and return the values
			return current->value;
		}
		current = current->next;
	}

	// Return NULL if the key is not found
	return (NULL);
}

void replace_envp(char **input, char *old, char *new)
{
	if (!new) // If new is NULL, don't replace
		return;

	char *pos = ft_strnstr(*input, old, ft_strlen(*input));
	if (!pos)
		return;

	int old_len = ft_strlen(old);
	int new_len = ft_strlen(new);
	int input_len = ft_strlen(*input);

	char *new_input = malloc(input_len - old_len + new_len + 1);
	if (!new_input)
		return;

	// Copy part before `old`
	ft_strlcpy(new_input, *input, pos - *input + 1);

	// Append `new`
	ft_strlcat(new_input, new, (pos - *input) + new_len + 1);

	// Append part after `old`
	ft_strlcat(new_input, pos + old_len, input_len - old_len + new_len + 1);

	free(*input);
	*input = new_input;
}

pid_t ft_getpid(void)
{
	int fd;
	char buffer[256];
	ssize_t bytesRead;
	pid_t pid = -1;

	// Open the /proc/self/status file
	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
	{
		return -1; // Error opening file
	}

	// Read the file content
	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesRead == -1)
	{
		close(fd);
		return -1; // Error reading file
	}

	// Null-terminate the buffer to make it a proper string
	buffer[bytesRead] = '\0';

	// Look for the line starting with "Pid:"
	char *line = buffer;
	while (line)
	{
		if (strncmp(line, "Pid:", 4) == 0)
		{
			// Extract the PID from the line
			pid = (pid_t)strtol(line + 5, NULL, 10);
			break;
		}
		// Move to the next line
		line = strchr(line, '\n');
		if (line)
		{
			line++; // Move past the newline character
		}
	}

	// Close the file
	close(fd);

	return pid;
}

char *handle_double_dollar(char *input)
{
	char *pos;
	char pid_str[12];
	pid_t pid;

	// Get the current process ID
	pid = ft_getpid();
	sprintf(pid_str, "%d", pid);

	// Replace occurrences of $$ with the PID
	while ((pos = ft_strnstr(input, "$$", ft_strlen(input))) != NULL)
	{
		replace_envp(&input, "$$", pid_str);
	}

	return input;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to remove all occurrences of a specific character from a string
char *remove_char(char *str, char char_to_remove)
{
	if (!str)
		return NULL;

	int len = strlen(str);
	char *result = malloc(len + 1);
	if (!result)
		return NULL;

	char *ptr = result;
	int i = 0;
	while (i < len)
	{
		if (ft_isspace(str[i + 1]) && str[i] == char_to_remove)
		{
			*ptr++ = str[i++];
			*ptr++ = str[i++]; // Copy the escaped character
		}
		else if (str[i] != char_to_remove)
		{
			*ptr++ = str[i++];
		}
		else if (str[i] == char_to_remove && str[i + 1] == '\0')
		{
			*ptr++ = str[i++];
		}
		else
		{
			i++;
		}
	}
	*ptr = '\0';
	return result;
}
int ft_is_delimiter(char c)
{
	if (c == '$')
	{
		return 1;
	}
	if (c == '|' || c == '>' || c == '<')
	{
		return 1;
	}
	if (c == '\'' || c == '"')
	{
		return 1;
	}
	return 0;
}
// Function to parse and replace environment variables
char *handle_dollar_signe(char *input, t_env *envp_head)
{
	int i = 0;
	int start, end;
	char *sub_env;
	input = handle_double_dollar(input);

	while (input[i])
	{
		if (input[i] == '$' && ft_isdigit(input[i + 1]))
		{
			sub_env = ft_substr(input, i, 2);
			replace_envp(&input, sub_env, "");
			free(sub_env);
			i += 2;
		}
		else if (input[i] == '$')
		{
			i++;
			start = i;
			while (input[i] && !ft_isspace(input[i]) && !ft_is_delimiter(input[i]) || input[i] == '_')
				i++;
			end = i;
			sub_env = ft_substr(input, start, end - start);
			char *env_value = my_getenv_from_copy(sub_env, envp_head);
			if (env_value)
				replace_envp(&input, sub_env, env_value);
			else
				replace_envp(&input, sub_env, "");
			free(sub_env);
		}
		else
			i++;
	}
	return remove_char(input, '$');
}

// for test
int main(int argc, char **argv, char **envp)
{
	t_env *copy_envp = NULL;
	char *input;
	if (argc > 1)
	{
		printf("a%s", argv[1]);
	}

	// Initialize the copy_envp linked list from envp
	init_copy_envp(&copy_envp, envp);

	while (1)
	{
		input = readline("minishell>>> ");
		if (!input)
		{
			break;
		}
		if (*input)
		{
			add_history(input);
			// Update input after processing using the refactored function
			input = handle_dollar_signe(input, copy_envp);
			printf("%s\n", input);
		}
		free(input);
	}

	// Free the linked list and clean up
	free_list(copy_envp);

	return 0;
}