NAME		= cub3d

SRC			= src/main.c \
			  src/set_image_data.c \
			  src/hooks.c \
			  src/my_mlx_pixel_put.c \
			  src/render_next_frame.c \
			  src/draw_next_frame.c \
			  src/map.c

OBJ			= $(SRC:.c=.o)

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -g

MLX			= mlx/libmlx.a

MLX_LINUX	= mlx_linux/libmlx_Linux.a

LIBFT		= libft/libft.a

DETECTED_OS	= $(shell uname)

ifeq ($(DETECTED_OS), Linux)
$(NAME)		: $(OBJ) $(MLX_LINUX) $(LIBFT)
	$(CC) $(OBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

%.o			: %.c
	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@
else
$(NAME)		: $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(OBJ) -Llibft -lft -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o			: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@
endif

$(MLX)		:
	make -C mlx

$(MLX_LINUX):
	make -C mlx_linux

$(LIBFT)	:
	make -C libft

all			: $(NAME)

clean		:
	$(RM) $(OBJ)

fclean		: clean
	$(RM) $(NAME)
	make -C libft fclean

re			: fclean all

.PHONY		: mlx all clean fclean re
