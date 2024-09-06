/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:14:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/05 19:21:00 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_syntax_error(char *error_message, int *exit_status)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	write(2, error_message, ft_strlen(error_message));
	write(2, "'\n", 2);
	*exit_status = 2;
}

void	ft_print_error_message(char *arg1, char *arg2)
{
	char	*msg;

	if (arg1)
		msg = ft_strdup(arg1);
	if (arg2)
		msg = ft_strjoin(msg, arg2);
	msg = ft_strjoin(msg, "\n");
	write(2, msg, ft_strlen(msg));
	free(msg);
}
