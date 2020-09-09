# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: zeno <zeno@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/16 14:29:42 by zeno          #+#    #+#                  #
#    Updated: 2020/09/08 15:07:02 by zenotan       ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = main.c \
		utils/struct_utils.c \
		utils/mlx_utils.c \
		utils/drawing_utils.c \
		utils/bmp.c \
		parser/initial_parser.c \
		parser/parse_res_color.c \
		parser/parse_tex.c \
		parser/parse_utils.c \
		parser/parse_sprite.c \
		parser/parse_map.c \
		parser/flood_fill.c \
		engine/calc_sprite.c \
		engine/raycaster.c \
		engine/movement.c

LIBS = lft/libft.a \
	gnl/gnl.a
OBJ = $(SRC:%.c=%.o)
FLAGS = -Wall -Wextra -Werror -O3
CC = gcc
BMP = screenshot.bmp

MLX_DIR = mlx_mac
MLX_NAME = mlx
EXTRA = -framework OpenGL -framework AppKit
LEAKS = -fsanitize=address -g

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C lft/
	make -C gnl/
	cp $(MLX_DIR)/libmlx.dylib ./libmlx.dylib
	$(CC) $(FLAGS) $(LIBS) $(EXTRA) -L$(MLX_DIR) -l$(MLX_NAME) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(FLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(BMP)
	make clean -C lft/
	make clean -C gnl/
	make clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) libmlx.dylib
	make fclean -C lft/
	make fclean -C gnl/

re: fclean all