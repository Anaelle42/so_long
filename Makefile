NAME = so_long

SRC = 	map.c \
		parsing.c \
		parsing2.c 

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra
MLXFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0m
BOLD = \033[1m
FLASH = \033[6m
BANDE = \033[7m

all : minilibx $(NAME)

minilibx:
	@make -C minilibx-linux >/dev/null 2>&1
	@echo "${RED}${BOLD}	COUCOU MLX COMPILE"
	@echo "  /\_/\   "
	@echo " ( o.o )  "
	@echo "  > ^ <   ${WHITE}"

ft_libft :
	@make -s -C libft bonus

$(NAME) : ft_libft $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME) $(MLXFLAGS) libft/libft.a
	@echo "${YELLOW}${BOLD}	RECOUCOU FICHIERS COMPILES ${WHITE}"

.o : .c 
	cc $(CFLAGS) -c -o $< $@

clean :
	rm -f $(OBJ)
	make -C minilibx-linux clean >/dev/null 2>&1
	make -C libft clean

fclean : clean
	rm -f $(NAME)
	make -C libft fclean

re : fclean all
	@make -C minilibx-linux >/dev/null 2>&1

.PHONY : clean fclean re 
