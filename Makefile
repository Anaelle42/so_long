NAME = so_long
NAME_BONUS = so_long_bonus

SRC = 	so_long.c \
		parsing.c \
		parsing_utils.c \
		display_map.c \
		movements.c 

SRC_BONUS = so_long.c \
			parsing.c \
			parsing_utils.c \
			display_map.c \
			movements_bonus.c 

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

CFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext

RED = \033[0;31m
YELLOW = \033[0;33m
WHITE = \033[0m
BOLD = \033[1m
FLASH = \033[6m
BANDE = \033[7m

all : $(NAME)
bonus : $(NAME_BONUS)

minilibx-linux/libmlx.a:
	@make -C minilibx-linux >/dev/null 2>&1
	@echo "${RED}${BOLD}	MLX COMPILE"
	@echo "  /\_/\   "
	@echo " ( o.o )  "
	@echo "  > ^ <   ${WHITE}"

libft/libft.a :
	@make -s -C libft

$(NAME) : minilibx-linux/libmlx.a libft/libft.a $(OBJ)
	cc $(OBJ) -o $(NAME) $(MLXFLAGS) libft/libft.a
	@echo "${YELLOW}${BOLD}	FICHIERS COMPILES ${WHITE}"

$(NAME_BONUS): minilibx-linux/libmlx.a libft/libft.a $(OBJ_BONUS)
	cc $(OBJ_BONUS) -o $(NAME_BONUS) $(MLXFLAGS) libft/libft.a

.c.o:
	cc $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ) $(OBJ_BONUS)
	@make -C minilibx-linux clean >/dev/null 2>&1
	@make -s -C libft clean

fclean : clean
	rm -f $(NAME) $(NAME_BONUS)
	@make -s -C libft fclean

re : fclean all

.PHONY : clean fclean re 
