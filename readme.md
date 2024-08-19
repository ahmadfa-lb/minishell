👇🏻 use this command below to suppress the leaks caused by readline

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp ./minishell

