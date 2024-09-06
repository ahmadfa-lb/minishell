/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 04:56:29 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 14:36:57 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_normal_variable(char *input, int *i, char **result, t_env *env)
{
	int		start;
	int		end;
	char	*sub_env;
	char	*env_value;

	(*i)++;
	start = *i;
	while (input[*i]
		&& (ft_isalnum(input[*i]) || input[*i] == '_' || input[*i] == '\0'))
		(*i)++;
	end = *i;
	if (start != end)
	{
		sub_env = ft_substr(input, start, end - start);
		env_value = get_env(env, sub_env);
		if (env_value)
			*result = ft_strjoin(*result, env_value);
		free(sub_env);
	}
	else
		*result = ft_strjoin(*result, "$");
}

void	handle_two_dollar(char **result, int *i)
{
	char	*num_str;

	num_str = ft_itoa(getpid());
	*result = ft_strjoin(*result, num_str);
	*i += 2;
	free(num_str);
}

void	handle_dollarexitstatus(char **result, int exit_status, int *i)
{
	char	*string;

	string = ft_itoa(exit_status);
	*result = ft_strjoin(*result, string);
	*i += 2;
	free(string);
}

char	*handle_dollar_sign(char *input, t_env *env, int exit_status)
{
	int		i;
	char	*result;
	char	tmp[2];

	(i = 0, result = ft_strdup(""));
	while (i < ft_strlen1(input) && input[i])
	{
		if (input[i] == '$')
		{
			if (!input[i + 1])
				(result = ft_strjoin(result, "$"),i++);
			else if (input[i + 1] == '?')
				handle_dollarexitstatus(&result, exit_status, &i);
			else if (input[i + 1] == '$')
				(handle_two_dollar(&result, &i), i++);
			else if (ft_isdigit(input[i + 1]))
				i += 2;
			else
				handle_normal_variable(input, &i, &result, env);
		}
		else
			(ft_strlcpy(tmp, input + i, 2), result = ft_strjoin(result, tmp),
				i++);
	}
	return (result);
}
