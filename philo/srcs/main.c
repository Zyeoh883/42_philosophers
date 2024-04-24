/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:27:49 by zyeoh             #+#    #+#             */
/*   Updated: 2024/03/19 18:06:58 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	monitor(t_data *data, t_philo *philo)
{
	int	n;
	int	end;

	while (1)
	{
		end = 1;
		n = -1;
		while (++n < data->num_philo)
		{
			pthread_mutex_lock(&philo[n].philo_lock);
			if (data->meal_flag && philo[n].meals < data->maxnum_of_meals)
				end = 0;
			pthread_mutex_unlock(&philo[n].philo_lock);
			if (!alive(&philo[n]))
				return ;
		}
		if (data->meal_flag && end)
		{
			data->death = 1;
			return ;
		}
		usleep(200);
	}
}

int	check_done(t_data *data, t_philo *philo)
{
	int	n;

	monitor(data, philo);
	n = -1;
	while (++n < data->num_philo)
		pthread_join(philo[n].thread, NULL);
	return (0);
}

int	force_death(t_data *data)
{
	usleep(data->time_to_die * 1000);
	printf("%.4d %d died\n", data->time_to_die, 0);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_philo			philo[MAX_PHILO];
	pthread_mutex_t	mutex[MAX_PHILO];

	if (!parse(ac, av))
		return (EXIT_FAILURE);
	if (!initialize(ac, av, &data))
	{
		printf("init error\n");
		return (1);
	}
	if (!init_mutex(&data, mutex))
		return (0);
	if (!init_philo(&data, mutex, philo))
	{
		destroy_mutexes(&data, mutex);
		return (0);
	}
	if (!spawn_threads(&data, philo))
		return (0);
	if (ft_atoi(av[1]) == 1)
		return (force_death(&data));
	return (check_done(&data, philo));
}
