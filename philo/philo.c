/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 19:12:28 by jjhezane          #+#    #+#             */
/*   Updated: 2022/04/17 19:12:41 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philos;

	if (init_params(&info, argc, argv) && init_share(&info))
	{
		philos = init_philos(&info);
		if (!philos)
		{
			free(philos->info->sharable.forks);
			return (0);
		}
		run_simulation(philos);
		destroy_mutexes(&info);
		free(philos);
	}
	return (1);
}
