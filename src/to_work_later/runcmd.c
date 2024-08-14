/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: zmourtab <zakariamourtaban@gmail.com>      +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2024/08/01 10:22:42 by zmourtab          #+#    #+#             */
/*   Updated: 2024/08/02 00:08:06 by zmourtab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// runs cmd without any handling
void	runcmd(const char *input, char **env, t_data *data)
{
	pid_t pid;
	int status;

	data->cmd.running = 1;
	data->cmd.cmd = ft_split(input, ' ');
	pid = fork();
	if (pid == -1)
		printf("error in fork should be doing something here");
	if (pid == 0)
	{
		status = execve(get_path(data->cmd.cmd[0], env), data->cmd.cmd, env);
		if (status != 0)
		{
			printf("%s: command not found\n", data->cmd.cmd[0]);
			exit(status);
		}
		exit(status);
	}
	else
		data->cmd.pid = pid;
}
// handles cmd and executes,
// can be modified for future implementation of signals
void	initcmd(const char *input, char **env, t_data *data)
{
	
	if (input == NULL || *input == '\0')
		return ;
	data->cmd.running = 1;
	//! only for current testing will be removed later in development
	runcmd(input, env, data);
	waitpid(data->cmd.pid, &data->cmd.status, 0);
	data->cmd.running = 0;
}
