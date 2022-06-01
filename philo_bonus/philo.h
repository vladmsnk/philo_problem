/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:20:30 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/01 16:28:32 by jjhezane         ###   ########.fr       */
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
# include <sys/signal.h>
# include <semaphore.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>

# define SNAME "/mysem"
# define SPRINT "/prsem"
# define SDEAD "/dsem"
# define SKILL "/skill"

typedef	struct s_philo
{
	int				id;
	unsigned long	last_time_eat;
	int	curr_eat_amount;
}	t_philo;

typedef struct s_info
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_each_must_eat;
	unsigned long	time_of_start;
}	t_info;

typedef struct s_share
{
	sem_t	*sem;
	sem_t	*print_sem;
	sem_t	*dead_sem;
	sem_t	*print_kill_sem;
	int		*pids;
	int		killed;
	t_info	info;
	t_philo philo;
}	t_share;


int				init_params(t_share *share, int argc, char **argv);
int				init_share(t_share *share);
int				ft_atoi(const char *str);
unsigned long	get_time(void);
void    		print_helper(t_share *share, char *message);
void			ft_usleep(int time_to_wait);
void			run_simulation(t_share *share);
void			close_sems(t_share *share);

#endif