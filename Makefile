NAME	= fdf

CC		= gcc
RM		= rm -f
CFLAGS 	= -g -Wall -Wextra -Werror #-fsanitize=address

MINILIBX_DIR	:= minilibx_macos/
MINILIBX		:= $(MINILIBX_DIR)libmlx.a
MINILIBXCC		:= -I mlx -L $(MINILIBX_DIR) -lmlx
HEADER 			:= -I$(MINILIBX_DIR)
OPENGL			:= -framework OpenGL -framework AppKit


SRC	=	fdff.c
OBJ	=	$(SRC:%.c=%.o)

OBJF		=	.cache_exists

all:	makelibs
		@$(MAKE) $(NAME)

makelibs:
	@$(MAKE) -C $(MINILIBX_DIR)

$(NAME):	$(OBJ)		
			@$(CC) $(CFLAGS) $(OBJ) $(MINILIBXCC) $(OPENGL) -o $(NAME)		
			@echo "👉 $(CC) $(CFLAGS) $(OBJ) $(MINILIBXCC) $(OPENGL) -o $(NAME)"
			@echo "✨ FDF compiled!"

$(MINILIBX):
	@make -C $(MINILIBX_DIR)
	@echo "$(GREEN)Minilibx compiled!$(DEF_COLOR)"	

.PHONY:		all clean fclean re