#include "philo.h"

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

int	init_share(t_info info, t_share *share)
{
	share->sem = sem_open(SNAME, O_CREAT, 0644, info.num_of_philo);
	if (share->sem == SEM_FAILED)
		return (0);
	share->pids = (int *)malloc(sizeof(int) * info.num_of_philo);
	if (!share->pids)
	{
		sem_close(share->sem);
		sem_unlink(SNAME);
		return (0);
	}
	memset(share->pids, 1, info.num_of_philo);
	return (1);
}