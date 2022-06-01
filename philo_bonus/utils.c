/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:34:38 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/01 18:42:43 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_params(t_share *share, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		share->info.time_of_start = get_time();
		share->info.num_of_philo = ft_atoi(argv[1]);
		share->info.time_to_die = ft_atoi(argv[2]);
		share->info.time_to_eat = ft_atoi(argv[3]);
		share->info.time_to_sleep = ft_atoi(argv[4]);
		share->info.num_each_must_eat = -1;
		if (argc == 6)
			share->info.num_each_must_eat = ft_atoi(argv[5]);
		if (share->info.num_of_philo < 0 || share->info.time_to_die < 0
			|| share->info.time_to_eat < 0 || share->info.time_to_sleep < 0
			|| (share->info.num_each_must_eat != -1
				&& share->info.num_each_must_eat < 0))
			return (0);
		return (1);
	}
	return (0);
}

void	close_sems(t_share *share)
{
	sem_close(share->sem);
	sem_close(share->print_sem);
	sem_close(share->dead_sem);
	sem_close(share->print_kill_sem);
	sem_unlink(SNAME);
	sem_unlink(SPRINT);
	sem_unlink(SDEAD);
	sem_unlink(SEMKILL);
}

int	init_sems(t_share *share)
{
	close_sems(share);
	share->print_sem = sem_open(SPRINT, O_CREAT, 0644, 1);
	if (share->print_sem == SEM_FAILED)
		return (0);
	share->sem = sem_open(SNAME, O_CREAT, 0644, share->info.num_of_philo);
	if (share->sem == SEM_FAILED)
	{
		sem_close(share->print_sem);
		sem_unlink(SPRINT);
		return (0);
	}
	share->dead_sem = sem_open(SDEAD, O_CREAT, 0644, 1);
	share->print_kill_sem = sem_open(SEMKILL, O_CREAT, 0644, 1);
	if (share->dead_sem == SEM_FAILED)
	{
		sem_close(share->print_sem);
		sem_close(share->sem);
		sem_unlink(SPRINT);
		sem_unlink(SDEAD);
		return (0);
	}
	return (1);
}

int	init_share(t_share *share)
{
	int	num_of_p;

	num_of_p = share->info.num_of_philo;
	if (!init_sems(share))
		return (0);
	share->pids = (int *)malloc(sizeof(int) * num_of_p);
	if (!share->pids)
	{
		sem_close(share->sem);
		sem_unlink(SNAME);
		return (0);
	}
	share->philo.id = 0;
	share->killed = 0;
	share->philo.last_time_eat = 0;
	share->philo.curr_eat_amount = 0;
	memset(share->pids, 1, num_of_p);
	return (1);
}
