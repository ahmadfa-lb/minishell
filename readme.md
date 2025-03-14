# Minishell

Minishell is a minimalistic Unix shell implementation for the 42 curriculum. It replicates the behavior of Bash for basic command execution, redirections, pipes, and environment variable handling.


## Screenshots
### Running Minishell
![Minishell Screenshot](./screenshot.png)

## Features
- Command execution with arguments
- Built-in commands (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`)
- Environment variable expansion (`$VAR`)
- Redirections (`>`, `>>`, `<`)
- Pipes (`|` support for chaining commands)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Heredoc (`<<`) support

## Built-in Commands
- `echo` - Prints text to the terminal
- `cd` - Changes the current directory
- `pwd` - Prints the current directory path
- `export` - Sets an environment variable
- `unset` - Removes an environment variable
- `env` - Prints all environment variables
- `exit` - Exits the shell

## Example Usage
```bash
minishell$ echo "Hello, World!"
Hello, World!

minishell$ export MYVAR=42
minishell$ echo $MYVAR
42

minishell$ ls | grep minishell
minishell.c

minishell$ cat << EOF
> This is a heredoc example
> EOF
This is a heredoc example
```


