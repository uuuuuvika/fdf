SRCS	= fdf.c

OBJS	:= $(SRCS:%.c=%.o)

NAME	= fdf

CC		= cc -g
RM		= rm -f

CFLAGS 	= -Wall -Wextra -Werror #-fsanitize=address

all:		${NAME}

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME): $(OBJ)

	@make -C mlx
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

minilibx:
		make -C mlx

clean:
			make clean -C mlx
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all