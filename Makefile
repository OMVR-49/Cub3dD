# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sacharai <sacharai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/07 22:04:37 by ojebbari          #+#    #+#              #
#    Updated: 2024/03/27 06:44:58 by sacharai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c  Raycasting/raycasting1.c Raycasting/raycasting2.c \
		Raycasting/raycasting3.c Raycasting/raycasting4.c tools.c \
		Parsing/parsing.c get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c Parsing/ft_split.c \
		Parsing/ft_atoi.c Parsing/parsing_help.c \
				Parsing/parsing_help1.c \
				Parsing/parsing_help2.c \
				Parsing/parsing_help3.c \
				Parsing/parsing_help4.c \
				Parsing/insert_node.c \
				tools1.c \
				
SRS_BNS =	./bonus/main_bonus.c ./bonus/Raycasting/raycasting1_bonus.c \
			./bonus/Raycasting/raycasting2_bonus.c \
			./bonus/Raycasting/raycasting3_bonus.c \
			./bonus/Raycasting/raycasting4_bonus.c \
			./bonus/Raycasting/raycasting5_bonus.c \
			./bonus/tools_bonus.c ./bonus/Parsing/parsing_bonus.c \
			./bonus/Parsing/parsing_help_bonus.c \
			./bonus/get_next_line/get_next_line_bonus.c \
			./bonus/get_next_line/get_next_line_utils_bonus.c \
			./bonus/Parsing/ft_split_bonus.c \
			./bonus/Parsing/ft_atoi_bonus.c \

CFLAGS =   -g3 #-Wall -Wextra -Werror
CC = cc
NAME = cub3D
NAME_BONUS = cub3D_bonus
RM = rm -fr
OBJ = $(SRC:.c=.o)
OBJ_BNS = $(SRS_BNS:.c=.o)

MLX =  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
MLX_FLG = MLX42/build/libmlx42.a

all : $(NAME)


$(NAME) : $(OBJ) Cub3d.h
	$(CC)  $(OBJ) $(CFLAGS) $(MLX) $(MLX_FLG) -o $@

$(NAME_BONUS) : $(OBJ_BNS) ./bonus/Cub3d_bonus.h
	$(CC) $(CFLAGS) $(MLX) $(MLX_FLG) -o $@ $(OBJ_BNS)

bonus : $(NAME_BONUS)

clean :
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_BNS)

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

re : fclean all
