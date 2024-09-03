/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:27:26 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/03 18:40:17 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int check_status_str(char *str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         if (!ft_isdigit(str[i]))
//         {
//             return (0);
//         }
//         i++;
//     }
//     return (1);
// }

// void ft_exit(char **args)
// {
//     int exit_status = 0; // Default exit status

//     if (args[2] != NULL)
//     {
//         printf("exit: too many arguments \n");
//         exit (1);
//     }
    
//     if (args[1] != NULL)
//     {
//         // Convert the provided status string to an integer
//         if (!check_status_str(args[1]))
//         {
//             printf("exit: %s: numeric argument required\n", args[1]);
//             exit(255); // Standard behavior for non-numeric arguments
//         }
//         exit_status = ft_atoi(args[1]);

//         // Ensure the exit status is within the range [0, 255]
//         if (exit_status < 0 || exit_status > 255)
//         {
//             printf("exit: %s: numeric argument in range required\n", args[1]);
//             exit(255);
//         }
//     }
//     else
//     {
//         printf("Exiting with status: %d\n", exit_status);
//         exit(0);
//     }
    
//     printf("Exiting with status: %d\n", exit_status);
//     exit(exit_status);
// }

int check_status_str(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
    {
        i++;
    }
    
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
int calculate_exit_status(int status)
{
    int res;

    res = status % 256; // Apply modulo 256
    while (res < 0)
    {
        res += 256; // Adjust for negative results to ensure the result is within the 0-255 range
    }

    return res;
}

int convert_and_validate_exit_status(char *arg)
{
    int exit_status;

    if (!check_status_str(arg))
    {
        printf("exit: %s: numeric argument required\n", arg);
        return 1; // Standard behavior for non-numeric arguments
    }

    exit_status = ft_atoi(arg);

    printf("exit: %d\n", calculate_exit_status(exit_status));
    return calculate_exit_status(exit_status);
}

void handle_too_many_args_error()
{
    printf("exit: too many arguments\n");
    exit(1);
}

int ft_exit(char **args)
{
    int exit_status;

    if (args[2] != NULL)
        handle_too_many_args_error();

    if (args[1] != NULL)
        exit_status = convert_and_validate_exit_status(args[1]);
    else
        exit_status = 0; // Default exit status

    //printf("Exiting with status: %d\n", exit_status);
    return(exit(exit_status),exit_status);
}
