# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emjoao <emjoao@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/06 11:59:13 by mosantos          #+#    #+#              #
#    Updated: 2026/03/20 17:56:59 by emjoao           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D
SRC_DIR		= src
LIBFT_DIR	= lib/libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR 	= ./minilibx-linux/
MLX_LIB 	= ./minilibx-linux/libmlx.a
MLXFLGAS 	= -Lminilibx-linux -lmlx -lXext -lX11 -lz -lm
CC                      = cc
CFLAGS          = -Wall -Wextra -g
RM                      = rm -rf

SRC			= $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/read/*.c $(SRC_DIR)/error_input/*.c $(SRC_DIR)/cleanup/*.c $(SRC_DIR)/execute/*.c $(SRC_DIR)/parsing/*.c $(SRC_DIR)/validation/*.c $(SRC_DIR)/utils/*.c $(SRC_DIR)/textures/*.c)
OBJ			= $(SRC:.c=.o)
HEADER		= $(wildcard $(SRC_DIR)/include/*.h)

all: $(NAME)

$(NAME): $(OBJ) $(MLX_LIB)
	@make -s -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(MLXFLGAS) $(LIBFT) -lm -o $(NAME)
	@echo "✅ [TENHO WILDCARD, DON'T FORGET]"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX_LIB):
	@make -s -C $(MLX_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	@make -s -C $(MLX_DIR) clean
	@$(RM) $(OBJ)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

