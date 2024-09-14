/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 12:44:16 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/14 15:40:38 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_ctrl_d(t_data *data)
{
	if (!data->user_input)
	{
		free_data(data);
		free(data);
		rl_clear_history();
		printf("exit\n");
		exit(0);
	}
}

void	handle_ctrl_c(int sig)
{
	g_signal_number = sig;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	update_exit_status_on_signal(int *status)
{
	if (g_signal_number == SIGINT)
	{
		*status = 130;
	}
	else if (g_signal_number == SIGQUIT)
	{
		*status = 131;
	}
	g_signal_number = 0;
}

// void	handle_execution_mode(int sig)
// {
// 	g_signal_number = sig;
// 	rl_replace_line("", 1);
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// }

void	handle_execution_mode(int sig)
{
	g_signal_number = sig;
	if (sig == SIGINT)
	{
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
		//rl_redisplay();
	}
}


void	handle_heredoc_ctrl_baskslash(int sig)
{
	g_signal_number = sig;
	//rl_replace_line("", 1);
}
