NAME=fdf

# CFLAGS= -Wextra -Wall -Werror -I/usr/local/include -g
CFLAGS 	= -g -Wall -Wextra  -I/usr/X11/include -fsanitize=address #-Werror
LIBFT= libs/the_libft/libft.a
FT_PRINTF= libs/ft_printf/libftprintf.a
#MLX = -L./libs/minilibx-linux -lmlx -lXext -lX11 -lm
INCLUDE	 		:= incl/
MINILIBX_DIR	:= libs/minilibx_macos/
MINILIBXCC		:= -I mlx -L $(MINILIBX_DIR) -lmlx
HEADER 			:= -I$(INCLUDE) -I$(MINILIBX_DIR)
OPENGL			:= -framework OpenGL -framework AppKit
CC=gcc

SRCS = fdf_utils.c	fdf.c colors_utils.c	colors.c	control.c	image.c utils_map.c \
		draw.c	draw_utils.c	utils.c	transform.c	to_3d.c	to_3d_utils.c
OBJS	:= ${SRCS:.c=.o}

RM=rm -rf

# $(MLX) :
# 	$(MAKE) -C ./libs/minilibx_macos

# $(LIBFT) :
# 	$(MAKE) -C ./libs/the_libft

# $(FT_PRINTF) :
# 	$(MAKE) -C ./libs/ft_printf

# all: $(NAME)
all:	makelibs
		@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(MINILIBX_DIR)
	$(MAKE) -C ./libs/the_libft
	$(MAKE) -C ./libs/ft_printf

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) $(MINILIBXCC) $(LIBFT) $(FT_PRINTF) $(OPENGL) -o $(NAME)

# $(MINILIBX):
# 	@make -C $(MINILIBX_DIR)

clean:
		@$(MAKE) clean -C $(MINILIBX_DIR)
		$(MAKE) clean -C ./libs/the_libft
		$(MAKE) clean -C ./libs/ft_printf
		$(RM) $(OBJS)

fclean: clean
		$(MAKE) fclean -C ./libs/the_libft
		$(MAKE) fclean -C ./libs/ft_printf
		$(RM) -f $(MINILIBX_DIR)libmlx.a	
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re