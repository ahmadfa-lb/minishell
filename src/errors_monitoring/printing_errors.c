/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_errors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:14:13 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/03 05:27:56 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_print_error_message(char *arg1, char *arg2)
{
	char	*msg;

	if (arg1)
		msg = ft_strdup(arg1);
	if (arg2)
		msg = ft_strjoin(msg, arg2);
	msg = ft_strjoin(msg, "\n");
	write(2, msg, ft_strlen(msg));
}
