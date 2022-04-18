/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjhezane <jjhezane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:22:42 by jjhezane          #+#    #+#             */
/*   Updated: 2022/04/18 19:53:32 by jjhezane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_info	info;
	t_share	share;

	if (init_params(&info, argc, argv) && init_share(info, &share))
	{
		run_simulation(info, &share);
	}
	
	return (0);
}