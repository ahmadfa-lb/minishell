/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:36:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/21 04:39:36 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_pid_line(int fd)
{
	static char	buffer[256];
	ssize_t		bytesRead;

	bytesRead = read(fd, buffer, sizeof(buffer) - 1);
	if (bytesRead <= 0) 
		return (NULL);
	buffer[bytesRead] = '\0';
	return (strstr(buffer, "Pid:"));
}

pid_t	ft_getpid()
{
	int		fd;
	char	*line;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1) {
		perror("open");
		return (-1);
	}
	line = read_pid_line(fd);
	close(fd);
	if (line != NULL)
		return ((pid_t)ft_atoi(line + 4));
	else
		return (-1);
}

char *handle_double_dollar(char *input)
{
    char *pos;
    char pid_str[12];
    pid_t pid;

    // Get the current process ID
    pid = ft_getpid();
    sprintf(pid_str, "%d", pid);

    // Replace occurrences of $$ with the PID
    while ((pos = ft_strnstr(input, "$$", ft_strlen(input))) != NULL)
    {
        replace_envp(&input, "$$", pid_str);
    }

    return input;
}