# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atable <atable@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/26 21:07:02 by atable            #+#    #+#              #
#    Updated: 2020/10/06 22:56:09 by atable           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d.a
GAME = cub3d
LIBFT = libft.a
MINILIBX = libmlx.a

LIBFT_DIR = libft
MINILIBX_DIR = minilibx

CC = gcc
FLAG = -Wall -Werror -Wextra
LIB_FLAG = -lcub3d -lft -lmlx -lXext -lX11 -lm
LIBS_PATH =	-L. -L$(LIBFT_DIR) -L$(MINILIBX_DIR)

SRC = check_func.c \
		create_3d_map.c \
		draw_rays.c \
		draw_sprites.c \
		free_func.c \
		get_next_line.c \
		initial_func.c \
		keyboard.c \
		main.c \
		make_bmp.c \
		make_func.c \
		moove_to_struct.c \
		skip_func.c \
		start_position.c \
		texture.c \
		utils.c
OBJ = $(SRC:.c=.o)
HDR = cub3d.h

SRC_PATH = srcs
OBJ_PATH = obj

.PHONY: all compile clean fclean re

all: $(GAME)

$(NAME): $(OBJ) | compile
	@ar rc $@ $?
	@ranlib $@

$(GAME): $(NAME)
	$(CC)  -o $(GAME) $(LIBS_PATH) $(LIB_FLAG)

%.o: $(SRC_PATH)/%.c $(SRC_PATH)/$(HDR)
	$(CC) -c $< -o $@

compile:
	make -C $(LIBFT_DIR) all
	make -C $(MINILIBX_DIR) all

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean
	make -C $(MINILIBX_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(GAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all