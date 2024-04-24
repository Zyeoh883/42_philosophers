/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:26:08 by zyeoh             #+#    #+#             */
/*   Updated: 2024/03/09 16:54:22 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_mutexes(t_data *data, pthread_mutex_t *mutex)
{
	int	n;

	pthread_mutex_destroy(&data->write);
	n = -1;
	while (++n < data->num_philo)
		if (!pthread_mutex_destroy(&mutex[n]))
			return (0);
	return (0);
}
