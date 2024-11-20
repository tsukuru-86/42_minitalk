# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsukuru <tsukuru@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 19:37:11 by tsukuru           #+#    #+#              #
#    Updated: 2024/11/20 19:37:14 by tsukuru          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server

# Directories
LIBFT_ALL_DIR = libft_all
INCLUDE_DIR = $(LIBFT_ALL_DIR)/include
SRC_DIR = $(LIBFT_ALL_DIR)/src
FT_PRINTF_DIR = $(SRC_DIR)/ft_printf
LIBFT_DIR = $(SRC_DIR)/libft

# Files
SRC_CLIENT = client.c
SRC_SERVER = server.c
FT_PRINTF_SRC = $(FT_PRINTF_DIR)/ft_printf.c \
                $(FT_PRINTF_DIR)/prt_hexa.c \
                $(FT_PRINTF_DIR)/prt_int.c \
                $(FT_PRINTF_DIR)/prt_ptr.c \
                $(FT_PRINTF_DIR)/prt_str.c \
                $(FT_PRINTF_DIR)/prt_unsigned.c
LIBFT_SRC = $(LIBFT_DIR)/ft_atoi.c \
            $(LIBFT_DIR)/ft_strlen.c \
			$(LIBFT_DIR)/ft_putchar_fd.c


# Compilation
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)

# Object files
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_PRINTF = $(FT_PRINTF_SRC:.c=.o)
OBJ_LIBFT = $(LIBFT_SRC:.c=.o)

# Targets
all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT) $(OBJ_PRINTF) $(OBJ_LIBFT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(OBJ_PRINTF) $(OBJ_LIBFT) -o $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(OBJ_PRINTF) $(OBJ_LIBFT)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(OBJ_PRINTF) $(OBJ_LIBFT) -o $(NAME_SERVER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER) $(OBJ_PRINTF) $(OBJ_LIBFT)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re

.SILENT: