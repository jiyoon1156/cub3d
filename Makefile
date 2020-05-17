MLX = -lmlx -framework Metal -framework Appkit

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c \
				srcs/ft_dotting.c \
				srcs/ft_error_check.c \
				srcs/ft_keypressed.c \
				srcs/ft_keypressed_2.c \
				srcs/ft_map.c \
				srcs/ft_parsing.c\
				srcs/ft_render.c\
				srcs/ft_save.c\
				srcs/ft_sprites.c\
				srcs/get_next_line.c\
				srcs/get_next_line_utils.c\
				srcs/libft_util.c\
				srcs/libft_util_2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME) : $(OBJS)
	cp minilibx/libmlx.dylib .
	$(CC) $(CFLAGS) $(OBJS) $(MLX) -L ./ -o $(NAME)

%.o: %.c $(INCS)
		$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f libmlx.dylib
	rm -f cub3d.bmp

re: fclean all