/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:39:55 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/09/06 05:57:31 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_to_home(t_env *env_list)
{
	char	*home;
	char	*pwd;

	home = get_env(env_list, "HOME");
	pwd = get_env(env_list, "PWD");
	if (home == NULL || chdir(home) != 0)
	{
		printf("minishell: cd: HOME not set\n");
		return (1);
	}
	set_env(&env_list, "OLDPWD", pwd, 0);
	set_env(&env_list, "PWD", home, 0);
	return (0);
}

int	cd_to_oldpwd(t_env *env_list)
{
	char	*old_pwd;
	char	*pwd;
	char	*new_pwd;

	old_pwd = get_env(env_list, "OLDPWD");
	pwd = get_env(env_list, "PWD");
	if (old_pwd == NULL || chdir(old_pwd) != 0)
	{
		printf("cd: %s: No such file or directory\n", old_pwd);
		return (1);
	}
	printf("%s\n", old_pwd);
	set_env(&env_list, "OLDPWD", pwd, 0);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	set_env(&env_list, "PWD", new_pwd, 0);
	free(new_pwd);
	return (0);
}

int	cd_to_path(char *path, t_env *env_list)
{
	char	*pwd;
	char	*new_pwd;

	pwd = get_env(env_list, "PWD");
	if (chdir(path) != 0)
	{
		printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	set_env(&env_list, "OLDPWD", pwd, 0);
	set_env(&env_list, "PWD", new_pwd, 0);
	free(new_pwd);
	return (0);
}

int	ft_cd(char **args, t_env *env_list)
{
	if (args[1] == NULL)
		return (cd_to_home(env_list));
	if (args[1][0] == '-' && args[1][1] == '\0')
		return (cd_to_oldpwd(env_list));
	if (args[1][0] == '-' && args[1][1] == '-')
	{
		printf("cd: --: invalid option\n");
		return (2);
	}
	if (args[2] == NULL)
		return (cd_to_path(args[1], env_list));
	write(STDERR_FILENO, "cd: too many arguments\n", 23);
	return (1);
}
