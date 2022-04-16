#include "philo.h"

void	print_info(t_philo *philo, char *msg)
{
		pthread_mutex_lock(&philo->info->sharable.cout);
		if (!philo->info->sharable.signal)
			printf("%lu %d %s\n", get_time() - philo->info->time_of_start, philo->id, msg);
		pthread_mutex_unlock(&philo->info->sharable.cout);
}