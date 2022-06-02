NAME =	philo

CC =	gcc
CFLAGS =	-g -Wall -Wextra -Werror -MMD

RM =	rm -rf

SRC =   philo.c \
		utils.c \
		time_utils.c \
		helper.c \
		ft_atoi.c \
		simulation.c \

INC =  philo.h \

OBJS =	$(SRC:.c=.o)
DEP =	$(SRC:.c=.d)

.PHONY :	all clean re fclean

$(NAME):	$(OBJS)
			${CC} ${CFLAGS} ${OBJS} -o ${NAME} -fsanitize=thread

all: 		$(NAME)

clean:
			$(RM) $(OBJS) $(DEP)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

-include $(DEP)