/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_uid_fetcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:36:54 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/17 14:18:28 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*read_pid_line(int fd)
{
	static char	buffer[256];
	ssize_t		bytes_read;

	bytes_read = read(fd, buffer, sizeof(buffer) - 1);
	if (bytes_read <= 0)
		return (NULL);
	buffer[bytes_read] = '\0';
	return (ft_strstr(buffer, "Pid:"));
}

pid_t	ft_getpid(void)
{
	int		fd;
	char	*line;

	fd = open("/proc/self/status", O_RDONLY);
	if (fd == -1)
	{
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

ssize_t	read_status_file(char *buffer, size_t size)
{
	int		fd;
	ssize_t	bytes_read;

	fd = open("/proc/self/status", O_RDONLY);
	bytes_read = -1;
	if (fd != -1)
	{
		bytes_read = read(fd, buffer, size - 1);
		close(fd);
	}
	return (bytes_read);
}

pid_t	ft_getuid(void)
{
	char	buffer[256];
	ssize_t	bytes_read;
	char	*uid_line;
	pid_t	uid;

	uid = -1;
	bytes_read = read_status_file(buffer, sizeof(buffer));
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
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
