/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:49:48 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/31 18:07:03 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool is_valid_n_flag(const char *arg)
{
    if (arg[0] != '-' || arg[1] != 'n')
        return false;

    for (int i = 1; arg[i] != '\0'; i++)
    {
        if (arg[i] != 'n')
            return false;
    }

    return true;
}
int ft_echo(char **args)
{
    bool newline = true;
    int i = 1;
    
    // Use the is_valid_n_flag function to check for multiple `-n` options
    while (args[i] && is_valid_n_flag(args[i]))
    {
        newline = false;
        i++;
    }

    // Print each argument separated by a space
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }

    // Print a newline unless "-n" was specified
    if (newline)
        printf("\n");
    return (0);
}


// char **convert_tokens_to_array(t_list_tokens *tokens_list)
// {
//     int count = 0;
//     t_list_tokens *current = tokens_list;
    
//     // Count the number of tokens
//     while (current)
//     {
//         count++;
//         current = current->next;
//     }

//     // Allocate memory for the array of strings
//     char **array = (char **)malloc(sizeof(char *) * (count + 1)); // +1 for the NULL terminator
//     if (!array)
//         return NULL;

//     // Populate the array with token values
//     current = tokens_list;
//     for (int i = 0; i < count; i++)
//     {
//         array[i] = strdup(current->value); // Duplicate the string value
//         current = current->next;
//     }
//     array[count] = NULL; // NULL-terminate the array

//     return array;
// }

// void	print_lines(int i, char **str, int out)
// {
// 	while (str[i])
// 	{
// 		ft_putstr_fd(str[i++], out);
// 		if (str[i])
// 			ft_putchar_fd(' ', out);
// 	}
// }

// int	ft_echo(t_cmd *cmd)
// {
// 	int		i;
// 	int		j;
// 	bool	n_option;
// 	t_list_tokens *current_token;

// 	i = 1;
// 	n_option = false;
// 	current_token = cmd->tokens_list; // Get the tokens list from the command

// 	// Skipping the first token which is "echo"
// 	if (current_token != NULL)
// 		current_token = current_token->next;

// 	// Check for the -n flag
// 	while (current_token && current_token->value[0] == '-'
// 		&& current_token->value[1] == 'n')
// 	{
// 		j = 1;
// 		while (current_token->value[j] == 'n')
// 			j++;
// 		if (current_token->value[j] == '\0')
// 			n_option = true;
// 		else
// 			break;
// 		current_token = current_token->next;
// 		i++;
// 	}

// 	// Convert the tokens list to an array of strings
// 	char **str_array = convert_tokens_to_array(cmd->tokens_list);

// 	// Print the lines after the flags
// 	print_lines(i, str_array, STDOUT_FILENO);

// 	// Print a newline unless "-n" was specified
// 	if (n_option == false)
// 		ft_putchar_fd('\n', STDOUT_FILENO);

// 	// Free the allocated array
// 	for (int k = 0; str_array[k] != NULL; k++)
// 		free(str_array[k]);
// 	free(str_array);
	
// 	return (EXIT_SUCCESS);
// }



