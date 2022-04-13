#include "philo.h"

void	*philo_action(void *data)
{
	t_philo *curr_philo;

	curr_philo =(t_philo *)data;
	// sleep(1);
	// pthread_mutex_lock(&curr_philo->info->sharable.cout);
	printf("%d\n", curr_philo->id);
	// pthread_mutex_unlock(&curr_philo->info->sharable.cout);
	return (NULL);
}


void	run_simulation(t_philo *philos)
{
	int	i;
	pthread_t *threads;
	int	num;

	i = 0;
	num = philos[0].info->num_of_philo;
	threads = (pthread_t *)malloc(sizeof(pthread_t) * num);
	if (!threads)
		return ;
	while (i < num)
	{
		pthread_create(&threads[i], NULL, philo_action, &philos[i]);
		i++;
	}
	i = 0;
	while (i < num)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}