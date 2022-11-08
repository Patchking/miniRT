NAME = miniRT

SRC_LST = main.c\
		  color_utils.c\
		  intersect_formulas.c\
		  vec_operations_0.c\
		  vec_operations_1.c\
		  vec_operations_2.c\
		  list.c\
		  ray_cast.c\
		  test.c\
		  destroy_win.c\
		  parse_amb_cam_lth.c\
		  parse_objects.c\
		  parse_utils_1.c\
		  parse_utils_2.c\
		  parse_utils_3.c\
		  parse.c\
		  pixel_put.c\
		  main_utils.c\
		  cyl_intersect_part_2.c\
		  ft_split.c\

SRC = $(addprefix $(SRC_DIR), $(SRC_LST))
LIB = $(MINILIBX) $(LIBFT)

INCLUDE = -I $(MINILIBX_HDR) -I $(SRC_HDR) -I $(LIBFT_HDR)
NEEDED_FLAGS = -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror
CC = gcc

MINILIBX_DIR = minilibx/
MINILIBX_HDR = $(MINILIBX_DIR)
MINILIBX = $(MINILIBX_DIR)libmlx.a

LIBFT_DIR = libft/
LIBFT_HDR = $(LIBFT_DIR)
LIBFT = $(LIBFT_DIR)libft.a

SRC_DIR = src/
SRC_HDR	= header/
OBJ_DIR = obj/
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
DEPENDS = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.d)

all:	$(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(OBJ_DIR) $(OBJ) Makefile
	$(CC) $(CFLAGS) $(LIB) -MMD $(INCLUDE) $(NEEDED_FLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(MINILIBX):
	make -sC $(MINILIBX_DIR)

$(LIBFT):
	make -sC $(LIBFT_DIR)

-include $(DEPENDS)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(SRC_HDR)
	$(CC) -c $(INCLUDE) $(CFLAGS) -MMD -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -sC $(MINILIBX_DIR) clean
	make -sC $(LIBFT_DIR) clean

fclean:
	rm -rf $(OBJ_DIR)
	rm -rf $(NAME)
	make -sC $(MINILIBX_DIR) clean
	make -sC $(LIBFT_DIR) fclean

re:	fclean all
