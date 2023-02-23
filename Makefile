NAME = pipex
CFLAGS := -Wall -Wextra -Werror -MMD -MP -g
LDFLAGS := -L libft -lft
CC = clang
SRC = pipex.c utils.c exec.c
DEP = $(SRC:.c=.d)
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -rf $(DEP) $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
