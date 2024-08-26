/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/26 11:14:29 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_normal_variable(char *input, int *i, char **result, t_env *env)
{
	int start;
	int end;
	char *sub_env;
	char *env_value;

	(*i)++;
	start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
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
char	*handle_dollar_sign(char *input, t_env *env)
{
	int		i;
	char	*result;
	char	tmp[2];

	i = 0;
	result = ft_strdup("");
	while (i < ft_strlen1(input) && input[i])
		if (input[i] == '$')
		{
			// if (input[i + 1] == '?')
				// handle_exit..
			if (input[i + 1] == '$')
				handle_two_dollar(&result, &i);
			else if (ft_isdigit(input[i + 1]))
				i += 2;
			else
				handle_normal_variable(input, &i, &result, env);
		}
		else
		{
			ft_strlcpy(tmp, input + i, 2);
			result = ft_strjoin(result, tmp);
			i++;
		}
	free(input);
	return (result);
}

t_list_tokens	*dollar_expansion(t_list_tokens *tokens_list, t_env *env)
{
	t_list_tokens	*current_token;
	
	current_token = tokens_list;
	while (current_token)
	{
		if (current_token->value && ft_strchr(current_token->value, '$') &&
		 current_token->quote_type != SINGLE_QUOTE)
			current_token->value = handle_dollar_sign(current_token->value, env);
		current_token = current_token->next;
	}
	return (tokens_list);
}
