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
NAME_BONUS			=	cub3D_bonus

CC					=	cc
CFLAGS				=	-O2 -Wall -Wextra -Werror

RM					=	rm -rf

SRC_DIR				=	src/
SRC_BONUS_DIR		=	src_bonus/

HEADER_DIR			=	includes/
HEADER				=	$(HEADER_DIR)cub3d.h
HEADER_BONUS		=	$(HEADER_DIR)cub3d.h

LIBFT_DIR			=	libft/
LIBFT				=	$(LIBFT_DIR)libft.a
LIBFT_FLAGS			=	-lft

MLX_DIR				=	minilibx_opengl/
MLX					=	$(MLX_DIR)libmlx.a
MLX_FLAGS			=	-lmlx -framework OpenGL -framework AppKit -lz

SRC_FILES			=	main.c\
						parser/parser.c\
						parser/parser_element_part.c\
						parser/parse_color.c\
						parser/check_map.c\
						utils/ft_clean.c\
						utils/utils.c\
						render/render.c\
						drawrays/drawrays.c\
						drawrays/halfjob.c\
						utils/initialization.c\
						game_loop/game_loop.c

SRC_BONUS_FILES		=	main.c\
						parser/parser.c\
						parser/parser_element_part.c\
						parser/parse_color.c\
						parser/check_map.c\
						utils/ft_clean.c\
						utils/utils.c\
						render/render.c\
						drawrays/drawrays.c\
						drawrays/halfjob.c\
						utils/initialization.c\
						game_loop/game_loop.c

OBJS				=	$(patsubst %.c, %.o, $(addprefix $(SRC_DIR), $(SRC_FILES)))
OBJS_BONUS			=	$(patsubst %.c, %.o, $(addprefix $(SRC_BONUS_DIR), $(SRC_BONUS_FILES)))

all					:	$(LIBFT) $(MLX) $(NAME)

$(LIBFT)			:
							make -C $(LIBFT_DIR)

$(MLX)				:
							make -C $(MLX_DIR)
							
$(NAME)				:	$(OBJS)
							$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) $(LIBFT_FLAGS) -L$(MLX_DIR) $(MLX_FLAGS) -o $@

%.o					:	%.c $(HEADER) $(HEADER_BONUS) Makefile
							$(CC) $(CFLAGS) -I$(HEADER_DIR) -I$(MLX_DIR) -c $< -o $@

bonus				:	$(LIBFT) $(MLX) $(NAME_BONUS)

$(NAME_BONUS)				:	$(OBJS_BONUS)
							$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) $(LIBFT_FLAGS) -L$(MLX_DIR) $(MLX_FLAGS) -o $@


clean				:
							$(RM) $(OBJS) $(OBJS_BONUS)
							make -C $(LIBFT_DIR) clean

fclean				:	clean
							$(RM) $(NAME) $(NAME_BONUS)
							make -C $(LIBFT_DIR) fclean
							make -C $(MLX_DIR) clean

re					:	fclean all

.PHONY				:	all clean fclean re