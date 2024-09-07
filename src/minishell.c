/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 10:22:42 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/06 20:15:10 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == ' '))
		i++;
	return (str[i] == '\0');
}

void	process_command(t_data *data)
{
	if (check_initial_errors(data->user_input, data))
	{
		split_tokens_by_pipe(data, &data->cmd_list);
		parse_all_redirections(data->cmd_list);
		data->env_array = env_list_to_array(data);
		data->exit_status = ft_execute_command(data, data->cmd_list);
		free_args(data->env_array);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(art(), (void)argc, (void)argv);
	data = ft_calloc(1, sizeof(t_data));
	data->env_list = init_copy_envp_to_list(envp);
	setup_initial_environment(&data->env_list);
	set_signals();
	while (1)
	{
		data->user_input = readline("minishell> ");
		handle_ctrl_d(data);
		update_exit_status_on_signal(&data->exit_status);
		if (!is_white_space(data->user_input))
			add_history(data->user_input);
		tokenize(data->user_input, &data->first_tokens_list);
		data->first_tokens_list
			= dollar_expansion(data->first_tokens_list, data);
		concate_nodes(&data->first_tokens_list);
		process_command(data);
		(free_tokens(data->first_tokens_list), free(data->user_input));
		(free_parser_list(data->cmd_list), data->cmd_list = NULL);
		data->first_tokens_list = NULL;
	}
	rl_clear_history();
	return (free_envp_list(data->env_list), free(data->env_array), 0);
}
