/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlad <vlad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 18:22:42 by jjhezane          #+#    #+#             */
/*   Updated: 2022/05/25 14:05:28 by vlad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_share	share;

	if (init_params(&share, argc, argv) && init_share(&share))
	{
		run_simulation(&share);
	}
	
	return (0);
}