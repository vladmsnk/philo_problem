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
			|| (share->info.num_each_must_eat != -1 && share->info.num_each_must_eat < 0))
			return (0);
		return (1);
	}
	return (0);
}


int	init_share(t_share *share)
{
	int	num_of_p;

	num_of_p = share->info.num_of_philo;
	share->print_sem = sem_open(SPRINT, O_CREAT, 0644, 1);
	if (share->print_sem == SEM_FAILED)
		return (0);
	share->sem = sem_open(SNAME, O_CREAT, 0644, num_of_p);
	if (share->sem == SEM_FAILED)
	{
		sem_close(share->print_sem);
		sem_unlink(SPRINT);
		return (0);
	}
	share->pids = (int *)malloc(sizeof(int) * num_of_p);
	if (!share->pids)
	{
		sem_close(share->sem);
		sem_unlink(SNAME);
		return (0);
	}
	share->philo.id = 0;
	share->philo.last_time_eat = 0;
	share->philo.curr_eat_amount = 0;
	memset(share->pids, 1, num_of_p);
	return (1);
}