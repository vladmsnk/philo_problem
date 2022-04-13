#include "philo.h"

void	destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
		pthread_mutex_destroy(&info->sharable.forks[i++]);
	free(info->sharable.forks);
}

int	init_share(t_info *info)
{
	int	i;
	info->sharable.forks = 
			(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
	if (!info->sharable.forks)
		return (0);
	i = 0;
	while (i < info->num_of_philo)
	{
		if (pthread_mutex_init(&info->sharable.forks[i], NULL) != 0)
		{
			free(info->sharable.forks);
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&info->sharable.cout , NULL) != 0)
		return (0);
	return (1);
}

int	init_params(t_info *info, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		info->num_of_philo = ft_atoi(argv[1]);
		info->time_to_die = ft_atoi(argv[2]);
		info->time_to_eat = ft_atoi(argv[3]);
		info->time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			info->num_each_must_eat = ft_atoi(argv[5]);
		if (info->num_of_philo < 0 || info->time_to_die < 0 
			|| info->time_to_eat < 0 || info->time_to_sleep < 0
				|| info->num_each_must_eat < 0)
				return (0);
		return (1);
	}
	return (0);
}

t_philo *init_philos(t_info *info)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * info->num_of_philo);
	if (!philos)
	{
		destroy_mutexes(info);
		return (NULL);
	}
	i = 0;
	while (i < info->num_of_philo)
	{
		philos[i].id = i + 1;
		philos[i].info = info;
		i++;
	}
	return (philos);
}