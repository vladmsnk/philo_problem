/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 19:37:07 by jjhezane          #+#    #+#             */
/*   Updated: 2022/04/18 21:10:16 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	handle_forks(sem_t *sem, int (*forker)(sem_t *))
{
	forker(sem);
	forker(sem);
}

void	start_philo_act(t_info info, t_share *share, t_philo i)
{
	share->sem = sem_open(SNAME, 0);
	
	handle_forks(share->sem, sem_wait);
	
	
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


void	run_simulation(t_info info, t_share *share)
{
	t_philo	philo;

	philo.id = 0;
	while (philo.id < info.num_of_philo)
	{
		share->pids[philo.id] = fork();

		if (share->pids[philo.id] == 0)
			start_philo_act(info, share, philo);
		else if (share->pids[philo.id] < 0)
			exit(EXIT_FAILURE);
		philo.id++;
	}
	wait_all_pids(share->pids, info.num_of_philo);
}