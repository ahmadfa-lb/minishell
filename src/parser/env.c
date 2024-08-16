/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:56:10 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/16 11:01:32 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// char	*find_path(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	if (!envp)
// 		return (NULL);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PATH", 4))
// 			i++;
// 		else
// 			return (envp[i] + 5);
// 	}
// 	return (NULL);
// }

// char	*find_pwd(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	if (!envp)
// 		return (NULL);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "PWD", 3))
// 			i++;
// 		else
// 			return (envp[i] + 4);
// 	}
// 	return (NULL);
// }

// char	*find_oldpwd(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	if (!envp)
// 		return (NULL);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "OLDPWD", 6))
// 			i++;
// 		else
// 			return (envp[i] + 7);
// 	}
// 	return (NULL);
// }

// char	*find_home(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	if (!envp)
// 		return (NULL);
// 	while (envp[i])
// 	{
// 		if (ft_strncmp(envp[i], "HOME", 4))
// 			i++;
// 		else
// 			return (envp[i] + 5);
// 	}
// 	return (NULL);
// }