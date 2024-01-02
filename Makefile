NAME	= fdf

CC		= gcc
RM		= rm -f
CFLAGS 	= -g -Wall -Wextra  -fsanitize=address #-Werror

LIBFT			= libs/the_libft/libft.a
MINILIBX_DIR	:= libs/minilibx_macos/
MINILIBXCC		:= -I mlx -L $(MINILIBX_DIR) -lmlx
OPENGL			:= -framework OpenGL -framework AppKit

SRC	=	fdf.c	utils_colors.c	keypress_handling.c	utils_image.c	utils_map.c
OBJ	=	$(SRC:%.c=%.o)

all:	makelibs
		@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(MINILIBX_DIR)
	$(MAKE) -C ./libs/the_libft

$(NAME):	$(OBJ)		
			@$(CC) $(CFLAGS) $(OBJ) $(MINILIBXCC) $(LIBFT) $(OPENGL) -o $(NAME)		

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

$(LIBFT) :
	$(MAKE) -C ./libs/the_libft

clean:
			@make clean -C $(MINILIBX_DIR)
			@make clean -C ./libs/the_libft
			$(RM) -rf $(OBJ)

fclean:		clean
			$(RM) -f $(NAME)
			@make fclean -C ./libs/the_libft
			$(RM) -f $(MINILIBX_DIR)libmlx.a		

re:			fclean
			@$(MAKE)

.PHONY:		all clean fclean re
