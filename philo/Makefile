NAME = philo

SRC = main.c utils.c init.c threads.c monitor.c routine_actions.c

OBJ = main.o utils.o init.o threads.o monitor.o routine_actions.o

CFLAGS = -Wall -Wextra -Werror -O3 -pthread

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	@rm -f $(OBJ)

go: all clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
