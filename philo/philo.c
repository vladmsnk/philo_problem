#include "philo.h"

int main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (init_params(&info, argc, argv) && init_share(&info))
	{
		philos = init_philos(&info);
		if (!philos)
			return (0);
		run_simulation(philos);
	}
	return (1);
}