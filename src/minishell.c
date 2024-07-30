/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:44:32 by afarachi          #+#    #+#             */
/*   Updated: 2024/07/30 04:44:33 by afarachi         ###   ########.fr       */
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
