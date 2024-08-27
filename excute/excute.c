/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouhamad_kraytem <mouhamad_kraytem@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:31:08 by mouhamad_kr       #+#    #+#             */
/*   Updated: 2024/08/26 13:01:00 by mouhamad_kr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// excute commad
//=> excute using execve

// handle built in command
//  handle cd , export , pwd , exit ...

// excute token
//  excute commands and take about | << >> < >

// ###################################################################

// >> (append output) : command >> file.txt
// => Purpose: Redirects the output of a command to a file, appending to the file rather than overwriting it.

// > : (output redirection) : command > file.txt
// => Purpose: Redirects the output of a command to a file, overwriting the file if it already exists.

// < : (input redirection) : command < file.txt
// Redirects input from a file to a command.

// << : (Here Document) :command << EOF
// This is some text.
// More text.
// EOF
// Used to feed a block of text to a command as if it were coming from a file stop when finding a specified text.

// | (pipe) : command1 | command2
// Connects the output of one command to the input of another.
