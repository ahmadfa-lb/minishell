/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_to_**array_conversion.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 05:17:59 by afarachi          #+#    #+#             */
/*   Updated: 2024/08/28 07:02:18 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_env_variables(t_env *env_list)
{
    int count;
	
	count = 0;
    while (env_list)
	{
        count++;
        env_list = env_list->next;
    }
    return (count);
}

static char **allocate_env_array(int count)
{
    char **env_array;
	
	env_array = malloc((count + 1) * sizeof(char *));
    if (!env_array)
        return NULL;
    env_array[count] = NULL;
    return (env_array);
}

static char *create_env_variable(t_env *env)
{
    int key_len; 
    int value_len; 
    char *env_var;

	key_len = strlen(env->key);
    value_len = strlen(env->value);
	env_var	= malloc(key_len + value_len + 2);
    if (!env_var)
        return NULL;
    strcpy(env_var, env->key);
    env_var[key_len] = '=';
    strcpy(env_var + key_len + 1, env->value);
    return (env_var);
}

char **env_list_to_array(t_data *data)
{
    int count;
    char **env_array;
	t_env *current;
	int i;

	count = count_env_variables(data->env_list);
    env_array = allocate_env_array(count);
    if (!env_array)
    {
        return NULL;
    }   
	current = data->env_list;
    i = 0;
    while (current)
	{
        env_array[i] = create_env_variable(current);
        if (!env_array[i])
		{
            while (i > 0)
                free(env_array[--i]);
            free(env_array);
            return (NULL);
        }
        current = current->next;
        i++;
    }
    return (env_array);
}
