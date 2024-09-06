/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 08:40:06 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 04:20:26 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_num_pipes(t_cmd *current_cmd)
{
	int	i;

	i = 0;
	while (current_cmd)
	{
		current_cmd = current_cmd->next;
		i++;
	}
	return (i);
}

void	close_parent_pipe(t_cmd *current_cmd, int **pipes, int i)
{
	if (current_cmd->prev)
		close(pipes[i - 1][0]);
	if (current_cmd->next)
		close(pipes[i][1]);
}

int	**create_pipes(int num_pipes)
{
	int	**pipes;
	int	i;

	pipes = (int **)malloc(sizeof(int *) * num_pipes);
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(pipes[i]) < 0)
		{
			perror("pipe");
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

void	set_pipes(t_cmd *current_cmd, int **pipes, int i, int num_pipes)
{
	if (current_cmd->prev)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (current_cmd->next)
		dup2(pipes[i][1], STDOUT_FILENO);
	close_all_pipes(pipes, num_pipes);
}
