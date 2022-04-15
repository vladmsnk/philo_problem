#include "philo.h"

void	handle_forks(t_philo *philo, int (*forker)(pthread_mutex_t *))
{
	forker(&philo->info->sharable.forks[philo->id - 1]);
	forker(&philo->info->sharable.forks[philo->id % philo->info->num_of_philo]);
}

void	*philo_action(void *data)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo *)data;
	if (!curr_philo->info->sharable.started)
	{
		if (curr_philo->id % 2 == 1)
			ft_usleep(50);
		curr_philo->info->sharable.started = 1;
	}
	while (!curr_philo->info->sharable.signal)
	{
		print_info(curr_philo, "is thinking");
		handle_forks(curr_philo, pthread_mutex_lock);
		print_info(curr_philo, "has taken a fork");
		print_info(curr_philo, "has taken a fork");
		print_info(curr_philo, "is eating");
		ft_usleep(curr_philo->info->time_to_eat);
		handle_forks(curr_philo, pthread_mutex_unlock);
		curr_philo->last_time_eat = get_time();
		curr_philo->eat_amount++;
		print_info(curr_philo, "is sleeping");
		ft_usleep(curr_philo->info->time_to_sleep);
	}
	return (NULL);
}


int test_philo_live(t_philo *philo)
{
	if (philo->last_time_eat && get_time() 
				- philo->last_time_eat > philo->info->time_to_die)
	{
		print_info(philo, "is died");
		philo->info->sharable.signal = 1;
		return (1);
	}
	if ( philo->eat_amount >= philo->info->num_each_must_eat)
		return (2);
	return (0);
}

int	monitoring(t_philo *philos)
{
	int	i;
	int	num;
	int flag;
	flag = 0;
	num = philos[0].info->num_of_philo;
	if (num == 1)
	{
		print_info(&philos[i], "is died");
		philos->info->sharable.signal = 1;
		return 1;
	}
	while (1)
	{
		i = 0;
		while (i < num)
		{
			if (philos[i].last_time_eat && get_time() 
				- philos[i].last_time_eat > philos[i].info->time_to_die)
			{
				print_info(&philos[i], "is died");
				philos->info->sharable.signal = 1;
				return (1);
			}
			i++;
		}
	}
	return (0);
}

void	run_simulation(t_philo *philos)
{
	int			i;
	pthread_t	*threads;
	int			num;

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
	if (monitoring(philos))
	{
		i = 0;
		while (i < num)
		{
			pthread_join(threads[i], NULL);;
			i++;
		}
	}
}