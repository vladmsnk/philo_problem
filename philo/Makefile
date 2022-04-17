NAME = philo

SRC = ft_atoi.c philo.c utils.c time_utils.c simulation.c print_helper.c

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

# NAME = philo

# SRC = ft_atoi.c philo.c utils.c time_utils.c simulation.c print_helper.c

# HDRS = philo.h 

# OBJ = $(SRC:.c=.o)

# CC = gcc

# CFLAGS = -Wall -Wextra -Werror -lpthread

# all: $(NAME)

# %.o: %.c $(HDRS)
# 	$(CC) $(CFLAGS) -c $< -o $@

# $(NAME): $(OBJ)
# 		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# clean:
# 	$(RM) $(OBJ)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re