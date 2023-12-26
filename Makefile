NAME	= fdf

CC		= gcc
RM		= rm -f
CFLAGS 	= -g -Wall -Wextra #-Werror #-fsanitize=address

MINILIBX_DIR	:= minilibx_macos/
MINILIBX		:= $(MINILIBX_DIR)libmlx.a
MINILIBXCC		:= -I mlx -L $(MINILIBX_DIR) -lmlx
HEADER 			:= -I$(MINILIBX_DIR)
OPENGL			:= -framework OpenGL -framework AppKit

SRC	=	fdff.c
OBJ	=	$(SRC:%.c=%.o)

all:	makelibs
		@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(MINILIBX_DIR)

$(NAME):	$(OBJ)		
			@$(CC) $(CFLAGS) $(OBJ) $(MINILIBXCC) $(OPENGL) -o $(NAME)		

$(MINILIBX):
	@make -C $(MINILIBX_DIR)

clean:
			@make clean -C $(MINILIBX_DIR)
			$(RM) -rf $(OBJ)

fclean:		clean
			$(RM) -f $(NAME)
			$(RM) -f $(MINILIBX_DIR)libmlx.a		

re:			fclean 
			@$(MAKE)

.PHONY:		all clean fclean re