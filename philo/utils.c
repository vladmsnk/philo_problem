/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:17:30 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/02 14:28:36 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->num_of_philo)
		pthread_mutex_destroy(&info->sharable.forks[i++]);
	pthread_mutex_destroy(&info->sharable.cout);
	free(info->sharable.forks);
}

int	init_share(t_info *info)
{
	int	i;

	info->sharable.forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * info->num_of_philo);
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
	if (pthread_mutex_init(&info->sharable.cout, NULL) != 0)
	{
		free(info->sharable.forks);
		return (0);
	}
	info->sharable.signal = 0;
	info->sharable.started = 0;
	info->sharable.must_eat_passed = 0;
	return (1);
}

int	*init_flags(int num)
{
	int	*flags;
	int	i;

	i = 0;
	flags = (int *)malloc(sizeof(int) * num);
	if (!flags)
		return (NULL);
	while (i < num)
		flags[i++] = 0;
	return (flags);
}

int	init_params(t_info *info, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		info->time_of_start = get_time();
		info->num_of_philo = ft_atoi(argv[1]);
		info->time_to_die = ft_atoi(argv[2]);
		info->time_to_eat = ft_atoi(argv[3]);
		info->time_to_sleep = ft_atoi(argv[4]);
		info->num_each_must_eat = -1;
		if (argc == 6)
			info->num_each_must_eat = ft_atoi(argv[5]);
		if (info->num_of_philo < 0 || info->time_to_die < 0
			|| info->time_to_eat < 0 || info->time_to_sleep < 0
			|| (info->num_each_must_eat != -1 && info->num_each_must_eat < 0))
			return (0);
		return (1);
	}
	return (0);
}

t_philo	*init_philos(t_info *info)
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
		philos[i].last_time_eat = 0;
		philos[i].eat_amount = 0;
		philos[i].info = info;
		i++;
	}
	return (philos);
}
