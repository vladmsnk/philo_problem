NAME = philo

SRC = ft_atoi.c philo.c utils.c

HDRS = philo.h 

OBJ = $(SRC:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -lpthread

all: $(NAME)

$(NAME): $(OBJ) $(HDRS)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re