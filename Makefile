# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 22:04:37 by ojebbari          #+#    #+#              #
#    Updated: 2024/03/22 15:56:53 by sacharai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c  Raycasting/raycasting1.c tools.c Parsing/parsing.c Parsing/parsing_help.c

CFLAGS =  -fsanitize=address -g3
CC = cc
NAME = cub3D
RM = rm -fr
OBJ = $(SRC:.c=.o)

MLX =  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MLX_FLG = MLX42/build/libmlx42.a

all : $(NAME)

%.o : %.c Cub3d.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) Cub3d.h
	$(CC)  $(OBJ) $(CFLAGS) $(MLX) $(MLX_FLG) -o $@

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
