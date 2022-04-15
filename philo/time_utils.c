#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval tv; 

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000); //in miliseconds
}

void	ft_usleep(int time_to_wait)  //in miliseconds
{
	unsigned long	time;

	time = get_time();
	while (get_time() < time + (unsigned long)time_to_wait)
		usleep(100);
}