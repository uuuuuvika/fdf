NAME	= fdf

CC		= gcc
RM		= rm -f
CFLAGS 	= -g -Wall -Wextra  -fsanitize=address #-Werror

LIBFT			:= libs/the_libft/
MINILIBX_DIR	:= libs/minilibx_macos/
MINILIBXCC		:= -I mlx -L $(MINILIBX_DIR) -lmlx
OPENGL			:= -framework OpenGL -framework AppKit

SRC	=	fdf.c	utils_colors.c	keypress_handling.c	utils_image.c
OBJ	=	$(SRC:%.c=%.o)

all:	makelibs
		@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(MINILIBX_DIR)
	@$(MAKE) -C $(LIBFT)

$(NAME):	$(OBJ)		
			@$(CC) $(CFLAGS) $(OBJ) $(MINILIBXCC) $(OPENGL) -o $(NAME)		

$(MINILIBX):
	@make -C $(MINILIBX_DIR)


clean:
			@make clean -C $(MINILIBX_DIR)
			@make clean -C $(LIBFT)
			$(RM) -rf $(OBJ)

fclean:		clean
			$(RM) -f $(NAME)
			$(RM) -f $(MINILIBX_DIR)libmlx.a		

re:			fclean 
			@$(MAKE)

.PHONY:		all clean fclean re
