# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvarys <gvarys@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 15:07:27 by gvarys            #+#    #+#              #
#    Updated: 2022/02/25 15:45:37 by gvarys           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	cub3D

CC					=	cc
CFLAGS				=	-O2 -Wall -Wextra -Werror

RM					=	rm -rf

SRC_DIR				=	src/

HEADER_DIR			=	includes/
HEADER				=	$(HEADER_DIR)cub3d.h

LIBFT_DIR			=	libft/
LIBFT				=	$(LIBFT_DIR)libft.a
LIBFT_FLAGS			=	-lft

MLX_DIR				=	minilibx_opengl/
MLX					=	$(MLX_DIR)mlx.a
MLX_FLAGS			=	-lmlx -framework OpenGL -framework AppKit

SRC_FILES			=	main.c\

OBJS				=	$(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))

all					:	$(LIBFT) $(MLX) $(NAME)

$(LIBFT)			:
							make -C $(LIBFT_DIR)

$(MLX)				:
							make -C $(MLX_DIR)
							
$(NAME)				:	$(OBJS)
							$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LIBFT_FLAGS) -L$(MLX_DIR) $(MLX_FLAGS) -o $@

%.o					:	%.c $(HEADER)
							$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

clean				:
							$(RM) $(OBJS)
							make -C $(LIBFT_DIR) clean

fclean				:	clean
							$(RM) $(NAME)
							make -C $(LIBFT_DIR) fclean
							make -C $(MLX_DIR) clean

re					:	fclean all

.PHONY				:	all clean fclean re