NAME=fdf

CFLAGS= -Wextra -Wall -Werror -I/usr/local/include -g
LIBFT= libs/the_libft/libft.a
FT_PRINTF= libs/ft_printf/libftprintf.a
MLX = -L./libs/minilibx-linux -lmlx -lXext -lX11 -lm
CC=cc

SRCS = fdf_utils.c	fdf.c colors_utils.c	colors.c	control.c	image.c utils_map.c \
		draw.c	draw_utils.c	utils.c	transform.c	to_3d.c	to_3d_utils.c
OBJS	:= ${SRCS:.c=.o}

RM=rm -rf

$(NAME): $(OBJS) $(MLX) $(LIBFT) $(FT_PRINTF)
	@$(CC) $(OBJS) $(MLX) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(MLX) :
	$(MAKE) -C ./libs/minilibx-linux

$(LIBFT) :
	$(MAKE) -C ./libs/the_libft

$(FT_PRINTF) :
	$(MAKE) -C ./libs/ft_printf

all: $(NAME)

clean:
		$(MAKE) clean -C ./libs/the_libft
		$(MAKE) clean -C ./libs/ft_printf
		$(RM) $(OBJS)

fclean: clean
		$(MAKE) fclean -C ./libs/the_libft
		$(MAKE) fclean -C ./libs/ft_printf
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re