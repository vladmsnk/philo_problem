#include "philo.h"

int main(int argc, char **argv)
{
	t_info info;
	t_philo *philos;
	int	i = 0;

	if (init_params(&info, argc, argv) && init_share(&info))
	{
		philos = init_philos(&info);
		if (!philos)
			return (0);
	}
	return (1);
}