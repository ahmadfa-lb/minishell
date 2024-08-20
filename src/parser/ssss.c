/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/20 08:12:45 by afarachi         ###   ########.fr       */
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

pid_t	ft_get_pid()
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
		return ((pid_t)atoi(line + 4));//we should use ft_atoi() instead atoi()
	else
		return (-1);
}

int main() {
    printf("The PID of this process is %d\n", ft_get_pid());
    return 0;
}