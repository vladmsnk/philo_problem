/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:13:42 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/01 18:29:29 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info->sharable.cout);
	if (!philo->info->sharable.signal)
		printf("%lu %d %s\n",
			get_time() - philo->info->time_of_start, philo->id, msg);
	pthread_mutex_unlock(&philo->info->sharable.cout);
}

void	handle_forks(t_philo *philo, int (*forker)(pthread_mutex_t *))
{
	forker(&philo->info->sharable.forks[philo->id - 1]);
	forker(&philo->info->sharable.forks[philo->id % philo->info->num_of_philo]);
}
