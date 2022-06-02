/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:14:34 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/02 14:30:28 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_action(void *data)
{
	t_philo	*curr_philo;

	curr_philo = (t_philo *)data;
	if (curr_philo->id % 2 == 1)
		ft_usleep(50);
	while (!curr_philo->info->sharable.signal)
	{
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
		print_info(curr_philo, "is thinking");
	}
	return (NULL);
}

int	test_philo_live(t_philo *philos, int num, int i, int *flags)
{
	static int	sum;

	if (philos->info->num_each_must_eat > 0
		&& philos[i].eat_amount >= philos->info->num_each_must_eat)
	{
		if (!flags[i])
			sum++;
		flags[i] = 1;
	}
	if (philos[i].last_time_eat && get_time()
		- philos[i].last_time_eat > (unsigned long)philos[i].info->time_to_die)
	{
		print_info(&philos[i], "died");
		philos->info->sharable.signal = 1;
		return (1);
	}
	if (sum == num)
	{
		free(flags);
		philos->info->sharable.signal = 1;
		sum = 0;
		return (1);
	}
	return (0);
}

int	monitoring(t_philo *philos)
{
	int	i;
	int	*flags;

	if (philos[0].info->num_of_philo == 1)
	{
		print_info(&philos[0], "died");
		philos->info->sharable.signal = 1;
		return (1);
	}
	flags = NULL;
	if (philos[0].info->num_of_philo > 0)
	{
		flags = init_flags(philos[0].info->num_of_philo);
		if (!flags)
			return (1);
	}
	i = 0;
	while (1)
	{
		if (test_philo_live(philos, philos[0].info->num_of_philo, i, flags))
			return (1);
		i = (i == philos[0].info->num_of_philo - 1) * 0
			+ (i != philos[0].info->num_of_philo - 1) * (i + 1);
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
			pthread_join(threads[i++], NULL);
	}
	free(threads);
}
