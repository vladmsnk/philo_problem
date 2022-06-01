/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:31:25 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/01 18:50:00 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_helper(t_share *share, char *message)
{
	sem_wait(share->print_sem);
	printf("%lu %d %s\n",
			get_time() - share->info.time_of_start,
			share->philo.id, message);
	sem_post(share->print_sem);
}

void	handle_forks(sem_t *sem, int (*forker)(sem_t *))
{
	forker(sem);
	forker(sem);
}
