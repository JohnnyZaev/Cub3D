# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ereginia <ereginia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/25 15:07:27 by gvarys            #+#    #+#              #
#    Updated: 2022/04/13 15:00:29 by ereginia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	cub3D

CC					=	cc
CFLAGS				=	-O2 -Wall -Wextra -Werror -g3

RM					=	rm -rf

SRC_DIR				=	src/

HEADER_DIR			=	includes/
HEADER				=	$(HEADER_DIR)cub3d.h

LIBFT_DIR			=	libft/
LIBFT				=	$(LIBFT_DIR)libft.a
LIBFT_FLAGS			=	-lft

MLX_DIR				=	minilibx_opengl/
MLX					=	$(MLX_DIR)libmlx.a
MLX_FLAGS			=	-lmlx -framework OpenGL -framework AppKit -lz

SRC_FILES			=	main.c\
						parser/parser.c\
						parser/parser_element_part.c\
						utils/ft_clean.c\
						utils/utils.c\
						render/render.c\

OBJS				=	$(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))

all					:	$(LIBFT) $(MLX) $(NAME)

$(LIBFT)			:
							make -C $(LIBFT_DIR)

$(MLX)				:
							make -C $(MLX_DIR)
							
$(NAME)				:	$(OBJS)
							$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LIBFT_FLAGS) -L$(MLX_DIR) $(MLX_FLAGS) -o $@

%.o					:	%.c $(HEADER) Makefile
							$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(MLX_DIR) -c $< -o $@

clean				:
							$(RM) $(OBJS)
							make -C $(LIBFT_DIR) clean

fclean				:	clean
							$(RM) $(NAME)
							make -C $(LIBFT_DIR) fclean
							make -C $(MLX_DIR) clean

re					:	fclean all

.PHONY				:	all clean fclean re