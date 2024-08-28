/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 22:39:55 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/28 22:45:33 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int cd_to_home(t_env *env_list)
{
    char *home = get_env(env_list, "HOME");
    char *pwd = get_env(env_list, "PWD");

    if (home == NULL || chdir(home) != 0)
    {
        perror("chdir failed");
        return 1;
    }
    set_env(&env_list, "OLDPWD", pwd);
    set_env(&env_list, "PWD", home);
    return 0;
}

int cd_to_oldpwd(t_env *env_list)
{
    char *old_pwd = get_env(env_list, "OLDPWD");
    char *pwd = get_env(env_list, "PWD");

    if (old_pwd == NULL || chdir(old_pwd) != 0)
    {
        perror("chdir failed");
        return 1;
    }

    // Update PWD and OLDPWD safely
    set_env(&env_list, "OLDPWD", pwd);
    char *new_pwd = getcwd(NULL, 0); // Use getcwd to get the current directory after chdir
    if (new_pwd == NULL)
    {
        perror("getcwd failed");
        return 1;
    }
    set_env(&env_list, "PWD", new_pwd);
    free(new_pwd);

    return 0;
}

int cd_to_path(char *path, t_env *env_list)
{
    char *pwd = get_env(env_list, "PWD");
    char *new_pwd;

    if (chdir(path) != 0)
    {
        perror("chdir failed");
        return 1;
    }
    new_pwd = getcwd(NULL, 0);
    if (new_pwd == NULL)
    {
        perror("getcwd failed");
        return 1;
    }
    set_env(&env_list, "OLDPWD", pwd);
    set_env(&env_list, "PWD", new_pwd);
    free(new_pwd);
    return 0;
}

int change_dir(char **args, t_env *env_list)
{
    if (args[1] == NULL)
    {
        return cd_to_home(env_list);
    }

    if (args[1][0] == '-' && args[1][1] == '\0')
    {
        return cd_to_oldpwd(env_list);
    }

    if (args[2] == NULL)
    {
        return cd_to_path(args[1], env_list);
    }

    fprintf(stderr, "cd: too many arguments\n");
    return 1;
}

//main for test if wou want
// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
//     char *input;
//     t_env *envp_list = init_copy_envp_to_list(envp);
//     t_list_tokens *tokens = NULL;

//     while ((input = readline("minishell> ")) != NULL)
//     {
//         if (*input == '\0')
//         {
//             free(input);
//             continue;
//         }

//         add_history(input);

//         tokenize(input, &tokens);

//         // Apply dollar expansion before concatenating nodes
//         tokens = dollar_expansion(tokens, envp_list); // Make sure to define or pass the `env` variable

//         concate_nodes(&tokens);

//         // t_list_tokens *current_token = tokens;
//         // while (current_token)
//         // {
//         //   printf("Token: %s, Value: %s, quote_type: %s, space: %d\n",
//         //      token_type_to_string(current_token->type),
//         //      current_token->value,
//         //      quote_type_to_string(current_token->quote_type),
//         //      current_token->space);
//         //   current_token = current_token->next;
//         // }

//         if (tokens && strcmp(tokens->value, "exit") == 0)
//         {
//             char **args = tokens_to_args(tokens);
//             handle_exit(args);
//             free_args(args);
//         }
//         else if (tokens && strcmp(tokens->value, "echo") == 0)
//         {
//             char **args = tokens_to_args(tokens);
//             execute_echo(args);
//             free_args(args);
//         }
//         else if (tokens && strcmp(tokens->value, "env") == 0)
//         {
//             char **args = tokens_to_args(tokens);
//             print_env(envp_list);
//             free_args(args);
//         }
//         else if (tokens && strcmp(tokens->value, "export") == 0)
//         {
//             char **args = tokens_to_args(tokens);
//             handle_export(&envp_list, args[1]);
//             free_args(args);
//         }
//         else if (tokens && strcmp(tokens->value, "unset") == 0)
//         {
//             char **args = tokens_to_args(tokens);
//             unset_env(&envp_list, args[0]);
//             free_args(args);
//         }
//         else if (tokens && strcmp(tokens->value, "cd") == 0)
//         {
//             char **args = tokens_to_args(tokens);
//             change_dir(args, envp_list);
//             free_args(args);
//         }

//         free_tokens(tokens);
//         tokens = NULL;
//         free(input);
//     }

//     free_envp_list(envp_list);
//     // free_tokens(tokens);
//     printf("\nExiting minishell...\n");
//     return 0;
// }