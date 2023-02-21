NAME = pipex

#FLAGS = -Wall -Wextra -Werror

CC = clang

SRC = pipex.c


OBJS = $(SRC: .c=.o)

all: $(NAME)

%.o: %.c pipex.h
	$(CC) -o -c $@ $< #$(FLAGS)

clean: 
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

.PHONY: all clean fclean re
