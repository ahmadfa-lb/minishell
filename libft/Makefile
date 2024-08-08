# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afarachi <afarachi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/07 09:28:36 by afarachi          #+#    #+#              #
#    Updated: 2024/08/07 09:33:05 by afarachi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME          = libft.a
FT_PRINTF_DIR = ft_printf/
GNL_DIR       = get_next_line/
FT_LIBFT_DIR  = ft_libft/
INC_DIR       = inc/
OBJ_DIR       = objs/

SRCS          = ${FT_LIBFT_DIR}ft_atoi.c \
                ${FT_LIBFT_DIR}ft_bzero.c \
                ${FT_LIBFT_DIR}ft_calloc.c \
                ${FT_LIBFT_DIR}ft_isalnum.c \
                ${FT_LIBFT_DIR}ft_isalpha.c \
                ${FT_LIBFT_DIR}ft_isascii.c \
                ${FT_LIBFT_DIR}ft_isdigit.c \
                ${FT_LIBFT_DIR}ft_isprint.c \
                ${FT_LIBFT_DIR}ft_memchr.c \
                ${FT_LIBFT_DIR}ft_strstr.c \
                ${FT_LIBFT_DIR}ft_memcmp.c \
                ${FT_LIBFT_DIR}ft_memcpy.c \
                ${FT_LIBFT_DIR}ft_memmove.c \
                ${FT_LIBFT_DIR}ft_memset.c \
                ${FT_LIBFT_DIR}ft_putchar_fd.c \
                ${FT_LIBFT_DIR}ft_putendl_fd.c \
                ${FT_LIBFT_DIR}ft_putnbr_fd.c \
                ${FT_LIBFT_DIR}ft_putstr_fd.c \
                ${FT_LIBFT_DIR}ft_strchr.c \
                ${FT_LIBFT_DIR}ft_strdup.c \
                ${FT_LIBFT_DIR}ft_split.c \
                ${FT_LIBFT_DIR}ft_strjoin.c \
                ${FT_LIBFT_DIR}ft_strlcat.c \
                ${FT_LIBFT_DIR}ft_strlcpy.c \
                ${FT_LIBFT_DIR}ft_strlen.c \
                ${FT_LIBFT_DIR}ft_strcmp.c \
                ${FT_LIBFT_DIR}ft_strncmp.c \
                ${FT_LIBFT_DIR}ft_strnstr.c \
                ${FT_LIBFT_DIR}ft_strrchr.c \
                ${FT_LIBFT_DIR}ft_strtrim.c \
                ${FT_LIBFT_DIR}ft_substr.c \
                ${FT_LIBFT_DIR}ft_tolower.c \
                ${FT_LIBFT_DIR}ft_toupper.c \
                ${FT_LIBFT_DIR}ft_strmapi.c \
                ${FT_LIBFT_DIR}ft_striteri.c \
                ${FT_LIBFT_DIR}ft_itoa.c \
                ${FT_LIBFT_DIR}ft_lstadd_back.c \
                ${FT_LIBFT_DIR}ft_lstadd_front.c \
                ${FT_LIBFT_DIR}ft_lstclear.c \
                ${FT_LIBFT_DIR}ft_lstdelone.c \
                ${FT_LIBFT_DIR}ft_lstiter.c \
                ${FT_LIBFT_DIR}ft_lstlast.c \
                ${FT_LIBFT_DIR}ft_lstnew.c \
                ${FT_LIBFT_DIR}ft_lstsize.c \
                ${FT_LIBFT_DIR}ft_lstmap.c \
                ${FT_PRINTF_DIR}ft_printf.c \
                ${FT_PRINTF_DIR}ft_printf_c.c \
                ${FT_PRINTF_DIR}ft_printf_d.c \
                ${FT_PRINTF_DIR}ft_printf_hex.c \
                ${FT_PRINTF_DIR}ft_printf_p.c \
                ${FT_PRINTF_DIR}ft_printf_s.c \
                ${FT_PRINTF_DIR}ft_printf_u.c \
                ${GNL_DIR}get_next_line.c \
                ${GNL_DIR}get_next_line_utils.c \
                ${GNL_DIR}get_next_line_bonus.c \
                ${GNL_DIR}get_next_line_utils_bonus.c

OBJS          = ${addprefix ${OBJ_DIR}, ${notdir ${SRCS:.c=.o}}}
CC            = cc
CFLAGS        = -Wall -Wextra -Werror

# Rule to compile .c files to .o files in the objs/ directory
${OBJ_DIR}%.o: ${FT_LIBFT_DIR}%.c
				@mkdir -p ${OBJ_DIR}
				${CC} ${CFLAGS} -I${INC_DIR} -c $< -o $@

${OBJ_DIR}%.o: ${FT_PRINTF_DIR}%.c
				@mkdir -p ${OBJ_DIR}
				${CC} ${CFLAGS} -I${INC_DIR} -c $< -o $@

${OBJ_DIR}%.o: ${GNL_DIR}%.c
				@mkdir -p ${OBJ_DIR}
				${CC} ${CFLAGS} -I${INC_DIR} -c $< -o $@

all:           ${NAME}

${NAME}:       ${OBJS} ${INC_DIR}libft.h ${INC_DIR}ft_printf.h ${INC_DIR}get_next_line.h ${INC_DIR}get_next_line_bonus.h
				ar rcs ${NAME} ${OBJS}

clean:
				rm -f ${OBJS}

fclean:        clean
				rm -f ${NAME}

re:            fclean all

.PHONY:        all clean fclean re
