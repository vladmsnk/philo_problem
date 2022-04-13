#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

typedef	struct s_share
{
	pthread_mutex_t *forks;
	pthread_mutex_t	cout;
	int				signal;
}	t_share;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int 			time_to_eat;
	int				time_to_sleep;
	int				num_each_must_eat;
	t_share			sharable;
}	t_info;

typedef	struct s_philo
{
	int				id;
	t_info			*info;
	pthread_t		home_t;
}	t_philo;

int	ft_atoi(const char *str);
int	init_params(t_info *info, int argc, char **argv);
int	init_share(t_info *info);
t_philo *init_philos(t_info *info);
#endif