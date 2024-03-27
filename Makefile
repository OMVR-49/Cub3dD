# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 22:04:37 by ojebbari          #+#    #+#              #
#    Updated: 2024/03/27 20:16:30 by sacharai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c  Raycasting/raycasting1.c Raycasting/raycasting2.c \
		Raycasting/raycasting3.c Raycasting/raycasting4.c Raycasting/raycasting5.c\
		tools.c Parsing/parsing.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c Parsing/ft_split.c \
		Parsing/ft_atoi.c Parsing/parsing_help.c \
				Parsing/parsing_help1.c \
				Parsing/parsing_help2.c \
				Parsing/parsing_help3.c \
				Parsing/parsing_help4.c \
				Parsing/insert_node.c \
				tools1.c \
				ft_grbg.c

CFLAGS = -O3 -Wall -Wextra -Werror 
CC = cc
NAME = cub3D
RM = rm -fr
OBJ = $(SRC:.c=.o)

MLX =  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MLX_FLG = MLX42/build/libmlx42.a

all : $(NAME)

%.o : %.c Cub3d.h
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJ) Cub3d.h
	@$(CC)  $(OBJ) $(CFLAGS) $(MLX) $(MLX_FLG) -o $@

clean :
	@$(RM) $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : fclean all
