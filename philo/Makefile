NAME = philo

SRC = ft_atoi.c philo.c utils.c time_utils.c simulation.c print_helper.c

HDRS = philo.h 

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -lpthread -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re