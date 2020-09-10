# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: zeno <zeno@student.codam.nl>                 +#+                      #
#                                                    +#+                       #
#    Created: 2020/05/16 14:29:42 by zeno          #+#    #+#                  #
#    Updated: 2020/09/10 21:23:17 by zenotan       ########   odam.nl          #
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
FLAGS = -Wall -Wextra -Werror 
CC = gcc
BMP = screenshot.bmp
OS = $(shell uname)
LEAKS = -fsanitize=address -g

ifeq ($(OS),Linux)
	MLX_DIR		=	mlxlinux
	MLX_NAME	=	mlx_Linux
	MLX_INCLUDE	=	mlxlinux
	DEFINE		=	-D LINUX=1
	EXTRA_FLAGS	=	-lz -lm -lX11 -lXext $(DEFINE)
else
	MLX_DIR		=	mlx_mac
	MLX_NAME	=	mlx
	MLX_INCLUDE	=	mlx
	DEFINE		=	-D MACOS=1
	EXTRA_FLAGS	=	-O3 -framework OpenGL -framework AppKit libmlx.dylib $(DEFINE)
endif

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_DIR)
	make -C lft/
	make -C gnl/
ifneq ($(OS),Linux)
	cp $(MLX_DIR)/libmlx.dylib .
endif
	$(CC) -o $(NAME) $(LIBS) $(OBJ) -L$(MLX_DIR) -l$(MLX_NAME) $(EXTRA_FLAGS)

%.o: %.c
	$(CC) $(FLAGS) -I$(MLX_DIR) -c $< -o $@ $(DEFINE)

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