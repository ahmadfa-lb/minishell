/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:14:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/02 16:41:08 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error_message(char *arg1, char *arg2)
{
	if (arg1)
		write(2, arg1, ft_strlen(arg1));
	if (arg2)
		write(2, arg2, ft_strlen(arg2));
	write(2, "\n", 1);
}