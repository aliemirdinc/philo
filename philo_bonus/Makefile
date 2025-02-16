NAME = philo_bonus

BONUS_SRC = main.c utils.c init.c threads.c monitor.c routine_actions.c

BONUS_OBJ = main.o utils.o init.o threads.o monitor.o routine_actions.o

CFLAGS = -Wall -Wextra -Werror -O3 -pthread

all: $(NAME)

$(NAME): $(BONUS_OBJ)
	@cc $(CFLAGS) $(BONUS_OBJ) -o $(NAME)

clean:
	@rm -f $(BONUS_OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
