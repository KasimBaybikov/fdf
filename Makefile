NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Imlx -g -fsanitize=address
MLXFLAGS = -framework OpenGL -framework AppKit -Lmlx -lmlx
MLX_D = mlx/
MLX = $(MLX_D)libmlx.a

FILES =	color.c\
		color_gets.c\
		get_next_line.c\
		get_next_line_utils.c\
		utils.c\
		utils_2.c\
		bresenham.c\
		draw.c\
		hooks.c\
		main.c\
		mlx.c\
		parse_map.c\
		xiaolin.c\

VPATH = srcs/colors/\
		srcs/gnl/\
		srcs/utils\
		srcs/\

HEADERS = includes/fdf.h\
		  includes/get_next_line.h\

FILES_O = $(addprefix objs/, $(notdir $(FILES)))
SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(FILES_O:.c=.o)
OBJDIR = objs/

objs/%.o : %.c Makefile $(HEADERS) 
	$(CC) $(CFLAGS) -c $< -o $@

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir objs/
$(NAME) : $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(MLXFLAGS) $(OBJS) -Lmlx -lmlx

$(MLX):
	$(MAKE) -C $(MLX_D) 2>/dev/null

clean:
	$(MAKE) -C $(MLX_D) clean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re: fclean all
