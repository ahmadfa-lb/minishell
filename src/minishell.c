/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42beirut.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 03:54:06 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 03:54:07 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

int main(int argc, char *argv[], char *envp[])
{
    
    return 0;
}
