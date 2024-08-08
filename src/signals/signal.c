/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 00:00:34 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/08 05:20:57 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handlesignal(t_data *data)
{
	if (data->cmd.running == 1)
		kill(data->cmd.pid, SIGINT);
	signalint = 0;
}

void	interactivehandle_sigint(int sig)
{
	signalint = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

// Function to handle SIGQUIT (Ctrl-\), which we will ignore
void	interactivehandle_sigquit(int sig)
{
	(void)sig;
}

void	noninteractivehandle_sigint(int sig)
{
	signalint = 1;
	printf("\n");
	(void)sig;
}

// Function to handle SIGQUIT (Ctrl-\), which we will ignore
void	noninteractivehandle_sigquit(int sig)
{
	(void)sig;
}
