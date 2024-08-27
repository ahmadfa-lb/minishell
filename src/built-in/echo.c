/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:49:48 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/27 14:52:32 by mouhamad_kr      ###   ########.fr       */
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
void execute_echo(char **args)
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
}