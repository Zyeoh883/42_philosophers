/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:31 by zyeoh             #+#    #+#             */
/*   Updated: 2024/03/09 01:03:07 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	long	result;
	int		sign;

	if (!str)
		return (0);
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	result = 0;
	while ('0' <= *str && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	return (result * sign);
}

int	init_mutex_array(pthread_mutex_t *result, int len)
{
	int	n;

	n = -1;
	while (++n < len)
	{
		if (pthread_mutex_init(&result[n], NULL) != 0)
		{
			while (--n >= 0)
				pthread_mutex_destroy(&result[n]);
			return (0);
		}
	}
	return (1);
}

int	init_mutex(t_data *data, pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (0);
	if (!init_mutex_array(mutex, data->num_philo))
	{
		pthread_mutex_destroy(&data->write);
		return (0);
	}
	return (1);
}

int	init_philo(t_data *data, pthread_mutex_t *mutex, t_philo *philo)
{
	int	n;

	n = -1;
	while (++n < data->num_philo)
	{
		memset(&philo[n], 0, sizeof(t_philo));
		philo[n].data = data;
		philo[n].id = n;
		philo[n].l_fork = &mutex[n];
		philo[n].r_fork = &mutex[(n + 1) % data->num_philo];
		if (pthread_mutex_init(&philo[n].philo_lock, NULL) != 0)
			return (0);
	}
	return (1);
}

int	initialize(int ac, char **av, t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->num_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->meal_flag = (ac == 6);
	if (ac > 5)
		data->maxnum_of_meals = ft_atoi(av[5]);
	return (1);
}
