NAME = philo_bonus

SRC = ft_atoi.c philo.c utils.c time_utils.c simulation.c

OBJ = $(SRC:.c=.o)
DEP = $(OBJ:.o=.d)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -MMD 

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) -lpthread $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ) $(DEP)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

include $(wildcard $(DEP))