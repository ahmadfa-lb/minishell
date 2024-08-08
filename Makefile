# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline

# Directories
SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = includes
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Executable
TARGET = minishell

# Targets
all: $(LIBFT_LIB) $(TARGET)

# Link the executable
$(TARGET): $(OBJS) $(LIBFT_LIB)
	@echo "Linking..."
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBFT_LIB)
	@echo "Compilation completed."

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
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
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Clean completed."

fclean: clean
	@rm -f $(TARGET)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
