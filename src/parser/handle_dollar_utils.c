/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:36:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/21 13:46:51 by afarachi         ###   ########.fr       */
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

ssize_t read_status_file(char *buffer, size_t size)
{
    int fd = open("/proc/self/status", O_RDONLY);
    ssize_t bytesRead = -1;
    if (fd != -1)
    {
        bytesRead = read(fd, buffer, size - 1);
        close(fd);
    }
    return (bytesRead);
}

pid_t ft_getuid()
{
    char buffer[256];
    ssize_t bytesRead;
    char *uid_line;
    pid_t uid = -1;

    bytesRead = read_status_file(buffer, sizeof(buffer));
    if (bytesRead > 0)
    {
        buffer[bytesRead] = '\0';
        uid_line = ft_strstr(buffer, "Uid:");
        if (uid_line)
        {
            uid_line = ft_strchr(uid_line, '\t');
            if (uid_line)
                uid = ft_atoi(uid_line + 1);
        }
    }
    return (uid);
}