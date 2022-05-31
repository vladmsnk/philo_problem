/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:37:07 by jjhezane          #+#    #+#             */
/*   Updated: 2022/05/25 15:51:57 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	handle_forks(sem_t *sem, int (*forker)(sem_t *))
{
	forker(sem);
	forker(sem);
}

int	monitoring(t_share *share)
{
	while (1)
	{
		if (share->philo.last_time_eat && get_time() 
		- share->philo.last_time_eat > (unsigned long)share->info.time_to_die)
		{
			print_helper(share, "died");
			kill(share->pids[share->philo.id], SIGUSR1);
		}
	}
	return (0);
}

void	start_philo_act(t_share *share)
{
	pthread_t monitor;

	pthread_cre
	if (share->philo.id % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		handle_forks(share->sem, sem_wait);
		print_helper(share, "has taken a fork");
		print_helper(share, "has taken a fork");
		print_helper(share, "is eating");
		ft_usleep(share->info.time_to_eat);
		handle_forks(share->sem, sem_post);
		share->philo.last_time_eat = get_time();
		share->philo.curr_eat_amount++;
		print_helper(share, "is sleeping");
		ft_usleep(share->info.time_to_sleep);
		print_helper(share, "is thinking");
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


void	run_simulation(t_share *share)
{

	while (share->philo.id < share->info.num_of_philo)
	{
		share->pids[share->philo.id] = fork();
		if (share->pids[share->philo.id] == 0)
		{
			start_philo_act(share);
			exit(EXIT_SUCCESS);
		}
		else if (share->pids[share->philo.id] < 0)
			exit(EXIT_FAILURE);
		share->philo.id++;
	}
	wait_all_pids(share->pids, share->info.num_of_philo);
}