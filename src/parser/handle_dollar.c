/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:46:31 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/21 13:43:32 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void replace_dollar_dollar(char **input, char *old, char *new)
{
	char *new_input;
	char *pos;
	int old_len;
	int new_len;
	int input_len;

    if (!new)
        return;
    pos = ft_strnstr(*input, old, ft_strlen(*input));
    if (!pos)
        return;
    old_len = ft_strlen(old);
    new_len = ft_strlen(new);
    input_len = ft_strlen(*input);
    new_input = malloc(input_len - old_len + new_len + 1);
    if (!new_input)
        return;
    ft_strlcpy(new_input, *input, pos - *input + 1);
    ft_strlcat(new_input, new, (pos - *input) + new_len + 1);
    ft_strlcat(new_input, pos + old_len, input_len - old_len + new_len + 1);
    free(*input);
    *input = new_input;
}

char *handle_double_dollar(char *input)
{
    char *pos;
    char *pid_str;
    pid_t pid;

    pid = ft_getpid();
    pid_str = ft_itoa(pid);
    while ((pos = ft_strnstr(input, "$$", ft_strlen(input))) != NULL)
        replace_dollar_dollar(&input, "$$", pid_str);
    free(pid_str);
    return input;
}

// Function to parse and replace environment variables
char *handle_dollar_sign(char *input, t_env *envp_head)
{
    int		i;
    int		start;
	int		end;
    char	*sub_env;
    char	*result;
	char	*env_value;
	char	tmp[2];
	
	i = 0;
	result = strdup("");
    input = handle_double_dollar(input);
    while (input[i])
    {
        if (input[i] == '$')
        {
            if (ft_isdigit(input[i + 1]))
            {
                i += 2;  // Skip the $ and digit
                continue;
            }
            i++;
            start = i;
            while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
                i++;
            end = i;

            if (start != end)  // If a valid variable name was found
            {
                sub_env = ft_substr(input, start, end - start);
                env_value = get_env(envp_head, sub_env);
                if (env_value)
                    result = ft_strjoin(result, env_value);  // Append the env value to result
                free(sub_env);
            }
            else
                result = ft_strjoin(result, "$");
        }
        else
        {
            tmp[0] = input[i];
            tmp[1] = '\0';
            result = ft_strjoin(result, tmp);
            i++;
        }
    }
    return (result);
}

