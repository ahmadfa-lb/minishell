# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 10:41:29 by afarachi          #+#    #+#              #
#    Updated: 2024/09/06 14:43:15 by afarachi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable
NAME = minishell

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -I$(INCLUDE_DIR)
LDFLAGS = -lreadline

# Source files and object files
SRCS = $(SRC_DIR)/lexer/input_to_tokens_list.c \
       $(SRC_DIR)/lexer/lexer_handlers.c \
       $(SRC_DIR)/lexer/list_tokens_concatenation.c \
       $(SRC_DIR)/lexer/tokenization_helpers.c \
       $(SRC_DIR)/parser/cmd_list_manager.c \
	   $(SRC_DIR)/parser/cmd_parsing.c \
	   $(SRC_DIR)/parser/dollar_expanssion.c \
	   $(SRC_DIR)/parser/dollar_handling.c \
	   $(SRC_DIR)/envp/envp.c \
	   $(SRC_DIR)/envp/env_utils.c \
	   $(SRC_DIR)/execute/execution.c \
	   $(SRC_DIR)/execute/execution_helpers.c \
	   $(SRC_DIR)/execute/file_checks_utils.c \
	   $(SRC_DIR)/execute/env_list_to_**array_conversion.c \
	   $(SRC_DIR)/execute/cmd_args_and_redirection.c \
	   $(SRC_DIR)/execute/path_and_cmd_validation.c \
	   $(SRC_DIR)/execute/pipe_management.c \
	   $(SRC_DIR)/execute/builtins_handling.c \
	   $(SRC_DIR)/errors_monitoring/printing_errors.c \
	   $(SRC_DIR)/errors_monitoring/syntax_error.c \
	   $(SRC_DIR)/builtins/cd.c \
	   $(SRC_DIR)/builtins/echo.c \
	   $(SRC_DIR)/builtins/export.c \
	   $(SRC_DIR)/builtins/unset.c \
	   $(SRC_DIR)/builtins/env.c \
	   $(SRC_DIR)/builtins/pwd.c \
	   $(SRC_DIR)/builtins/exit.c \
	   $(SRC_DIR)/heredocs/heredoc_handler.c \
	   $(SRC_DIR)/heredocs/heredoc_handler_helpers.c \
	   $(SRC_DIR)/memory_management/cleanup_utils.c \
	   $(SRC_DIR)/memory_management/cleanup_utils1.c \
	   $(SRC_DIR)/utils/utils.c \
	   $(SRC_DIR)/utils/buitins_utils.c \
	   $(SRC_DIR)/utils/ft_string_utils.c \
	   $(SRC_DIR)/utils/pid_uid_fetcher.c \
	   ${SRC_DIR}/minishell.c \
	   ${SRC_DIR}/art.c \
	   ${SRC_DIR}/signals/signals_helpers.c	\
	   ${SRC_DIR}/signals/signals.c	\
	   

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Colors
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

# Targets
all: $(NAME)
	@printf "\n"
	@echo $(G)"        _       _       _         _ _ "$(X)
	@echo $(G)" _____ |_| ___ |_| ___ | |_  ___ | | |"$(X)
	@echo $(G)"|     || ||   || ||_ - |   || -_|| | |"$(X)
	@echo $(G)"|_|_|_||_||_|_||_| ___||_|_||___ |_|_|"$(X)
	@printf "\n\n"

# Link the executable
$(NAME): $(OBJS) $(LIBFT_LIB)
	@echo "Linking..."
	@$(CC) -o $@ $(OBJS) $(LIBFT_LIB) $(LDFLAGS)
	@echo "Compilation completed."

# Rule to compile .c files to .o files in the obj/ directory
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)  # Create the necessary directories
	@echo -n "Compiling $<... "; \
	$(CC) $(CFLAGS) -c $< -o $@; \
	echo "done."

# Compile libft
$(LIBFT_LIB):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "Libft compilation completed."

# Clean up build artifacts
clean:
	@echo "Cleaning up..."
	@rm -rf $(OBJ_DIR)  # Remove all .o files and the obj directory
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Clean completed."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
