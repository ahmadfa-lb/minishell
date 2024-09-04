/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 10:55:56 by afarachi          #+#    #+#             */
/*   Updated: 2024/09/04 04:13:06 by afarachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *handle_heredoc(t_data *data, t_list_tokens *redirector) {
    char *line = NULL;
    char *temp_filename = generate_temp_filename();
    int fd;

    if (!temp_filename) {
        return NULL;  // Return if generating the temp filename failed
    }

    fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        free(temp_filename);
        return NULL;
    }

    // Loop until the delimiter is detected
    while (1) {
        line = readline("minishell> ");
        if (!line) {
            perror("readline");
            break;  // Exit loop if readline fails
        }

        // Check if the input matches the heredoc delimiter
        if (strcmp(line, redirector->value) == 0) {
            free(line);
            break;  // Break the loop if the delimiter is matched
        }

        // Write the input line to the temporary file
        write(fd, line, strlen(line));
        write(fd, "\n", 1);  // Add the newline character
        free(line);  // Free the line after writing it to the file
    }

    close(fd);
    return temp_filename;  // Return the name of the temporary file
}

// Send heredoc for commands
int send_heredoc(t_data *data) {
    t_cmd *cmd = data->cmd_list;  // Start with the first command
    int result = EXIT_SUCCESS;

    while (cmd) {
        if (cmd->list_redirectors && cmd->list_redirectors->type == TOKEN_HEREDOC) {
            // Generate the heredoc filename
            if (cmd->hd_file_name) {
                free(cmd->hd_file_name);  // Free the old filename if it exists
            }
            cmd->hd_file_name = handle_heredoc(data, cmd->list_redirectors);
            if (!cmd->hd_file_name) {
                result = EXIT_FAILURE;  // Handle failure to create heredoc
                break;
            }
        }
        cmd = cmd->next;  // Move to the next command
    }

    return result;  // Return the result of the heredoc processing
}
