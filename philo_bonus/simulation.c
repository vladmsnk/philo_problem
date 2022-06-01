/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:37:07 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/01 18:43:12 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitoring(void *share)
{
	t_share	*shr;

	shr = (t_share *)share;
	while (1)
	{
		if (shr->philo.last_time_eat && get_time()
			- shr->philo.last_time_eat > (unsigned long)shr->info.time_to_die)
		{
			sem_wait(shr->print_kill_sem);
			print_helper(share, "died");
			sem_wait(shr->print_sem);
			shr->killed = 1;
			sem_post(shr->dead_sem);
			sem_post(shr->print_kill_sem);
			return (NULL);
		}
		if (shr->philo.curr_eat_amount == shr->info.num_each_must_eat)
		{
			sem_post(shr->dead_sem);
			return (NULL);
		}
		usleep(1000);
	}
}

void	start_philo_act(t_share *share)
{
	if (share->philo.id % 2 == 0)
		ft_usleep(50);
	while (!share->killed)
	{
		handle_forks(share->sem, sem_wait);
		print_helper(share, "has taken a fork");
		print_helper(share, "has taken a fork");
		print_helper(share, "is eating");
		ft_usleep(share->info.time_to_eat);
		share->philo.last_time_eat = get_time();
		share->philo.curr_eat_amount++;
		handle_forks(share->sem, sem_post);
		if (!share->killed)
		{
			print_helper(share, "is sleeping");
			ft_usleep(share->info.time_to_sleep);
			print_helper(share, "is thinking");
		}
	}
}

void	wait_all_pids(int *pids, int num_of_forks)
{
	int	i;
	int	status;

	i = 0;
	while (i < num_of_forks)
		waitpid(pids[i++], &status, 0);
}

void	handle_killing(t_share	*share)
{
	int	checker;
	int	i;

	i = 0;
	checker = fork();
	if (checker == 0)
	{
		sem_wait(share->dead_sem);
		while (i < share->info.num_of_philo)
			kill(share->pids[i++], SIGTERM);
		sem_post(share->dead_sem);
		exit(EXIT_SUCCESS);
	}
}

void	run_simulation(t_share *share)
{
	pthread_t	monitor;

	sem_wait(share->dead_sem);
	while (share->philo.id < share->info.num_of_philo)
	{
		share->pids[share->philo.id] = fork();
		if (share->pids[share->philo.id] == 0)
		{
			pthread_create(&monitor, NULL, monitoring, share);
			start_philo_act(share);
			pthread_detach(monitor);
			exit(EXIT_SUCCESS);
		}
		else if (share->pids[share->philo.id] < 0)
			exit(EXIT_FAILURE);
		share->philo.id++;
	}
	handle_killing(share);
	wait_all_pids(share->pids, share->info.num_of_philo);
}
