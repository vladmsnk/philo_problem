/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:13:42 by jjhezane          #+#    #+#             */
/*   Updated: 2022/04/17 19:14:23 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->info->sharable.cout);
	if (!philo->info->sharable.signal)
		printf("%lu %d %s\n",
			get_time() - philo->info->time_of_start, philo->id, msg);
	pthread_mutex_unlock(&philo->info->sharable.cout);
}
