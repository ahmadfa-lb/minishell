/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:27:26 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/03 22:56:38 by mouhamad_kr      ###   ########.fr       */
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


long	ft_atol(const char *str)
{
	long int	nb;
	int			sign;

	nb = 0;
	sign = 1;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = (-1);
		str++;
	}
	while (ft_isdigit((int)*str))
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (sign * nb);
}

int check_status_str(char *str)
{
    int i;

    i = 0;
    if (str[i] == '-' || str[i] == '+')
        i++;
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

    return (res);
}
void handle_too_many_args_error()
{
    printf("exit: too many arguments\n");
    exit(1);
}

int convert_and_validate_exit_status(char **arg)
{
    long exit_status;

    if (!check_status_str(arg[1]))
    {
        printf("exit: %s: numeric argument required\n", arg[1]);
        return (2); // Standard behavior for non-numeric arguments
    }
    if (arg[2] != NULL)
    {
        handle_too_many_args_error();
        return (1);
    }
    
    exit_status = ft_atol(arg[1]);
    if (exit_status > LONG_MAX || exit_status < LONG_MIN)
    {
        printf("exit: %s: numeric argument required\n", arg[1]);
        return 2; // Standard behavior for non-numeric arguments
    }

    printf("exit: %d\n", calculate_exit_status((int)exit_status));
    return calculate_exit_status((int)exit_status);
}

int ft_exit(char **args)
{
    int exit_status;

    if (args[1] != NULL)
        exit_status = convert_and_validate_exit_status(args);
    else
        exit_status = 0; // Default exit status

    //printf("Exiting with status: %d\n", exit_status);
    return(exit(exit_status),exit_status);
}
