#include "philo.h"

void    print_helper(t_share *share, char *message)
{
	sem_wait(share->print_sem);
	printf("Philo: %d %s\n",share->philo.id, message);
	sem_post(share->print_sem);
}