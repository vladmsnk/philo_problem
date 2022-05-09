/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:37:07 by jjhezane          #+#    #+#             */
/*   Updated: 2022/05/09 15:13:05 by jjhezane         ###   ########.fr       */
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
			kill(share->pids[share->philo.id], SIGUSR1);
	}
	

	return (0);
}

void	start_philo_act(t_share *share)
{
	pthread_t	check_thr;

	pthread_create(&check_thr, NULL, monitoring, &share);
	pthread_detach(&check_thr);
	
	share->sem = sem_open(SNAME, 0);
	
	handle_forks(share->sem, sem_wait);
	
	// handle_forks(share->sem, sem_post);
	
	exit(EXIT_SUCCESS);
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
	t_philo	philo;

	philo = share->philo;
	while (philo.id < share->info.num_of_philo)
	{
		share->pids[philo.id] = fork();

		if (share->pids[philo.id] == 0)
			start_philo_act(share);
		else if (share->pids[philo.id] < 0)
			exit(EXIT_FAILURE);
		philo.id++;
	}
	wait_all_pids(share->pids, share->info.num_of_philo);
}