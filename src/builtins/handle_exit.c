/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:27:26 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/31 10:57:35 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_status_str(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!ft_isdigit(str[i]))
        {
            return (0);
        }
        i++;
    }
    return (1);
}

void simulate_exit(char **args)
{
    int exit_status = 0; // Default exit status

    if (args[2] != NULL)
    {
        printf("exit: too many arguments \n");
        exit (1);
    }
    
    if (args[1] != NULL)
    {
        // Convert the provided status string to an integer
        if (!check_status_str(args[1]))
        {
            printf("exit: %s: numeric argument required\n", args[1]);
            exit(255); // Standard behavior for non-numeric arguments
        }
        exit_status = ft_atoi(args[1]);

        // Ensure the exit status is within the range [0, 255]
        if (exit_status < 0 || exit_status > 255)
        {
            printf("exit: %s: numeric argument in range required\n", args[1]);
            exit(255);
        }
    }
    else
    {
        printf("Exiting with status: %d\n", exit_status);
        exit(0);
    }
    
    printf("Exiting with status: %d\n", exit_status);
    exit(exit_status);
}