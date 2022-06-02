/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:22:42 by jjhezane          #+#    #+#             */
/*   Updated: 2022/06/02 14:19:02 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_share	share;

	if (init_params(&share, argc, argv) && init_share(&share))
	{
		if (share.info.num_of_philo == 1)
		{
			share.philo.id = 1;
			print_helper(&share, "died");
			return (0);
		}
		run_simulation(&share);
	}
	return (0);
}
