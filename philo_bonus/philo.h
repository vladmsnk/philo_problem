/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:20:30 by jjhezane          #+#    #+#             */
/*   Updated: 2022/04/18 19:51:04 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <string.h>

# define SNAME "/mysem"

typedef	struct s_philo
{
	int				id;
	unsigned long	last_time_eat;
}	t_philo;

typedef struct s_share
{
	sem_t	*sem;
	int		*pids;
}	t_share;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_each_must_eat;
	unsigned long	time_of_start;
}	t_info;

int	init_params(t_info *info, int argc, char **argv);
int	init_share(t_info info, t_share *share);
int	ft_atoi(const char *str);
unsigned long	get_time(void);
void	ft_usleep(int time_to_wait);
void	run_simulation(t_info info, t_share *share);

#endif