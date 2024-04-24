/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:12:26 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 18:14:41 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_is_all_digits(char *str)
{
	if (!str || !*str)
		return (0);
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	parse(int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf(ERROR_FORMAT);
		return (0);
	}
	while (--ac > 0)
	{
		if (!ft_is_all_digits(av[ac]))
		{
			printf(ERROR_INPUT_TYPE);
			return (0);
		}
		if (ft_atoi(av[ac]) <= 0)
		{
			printf(ERROR_INPUT_TYPE);
			return (0);
		}
	}
	return (1);
}

size_t	gettime(struct timeval time_prev)
{
	struct timeval	time_now;

	gettimeofday(&time_now, NULL);
	return ((time_now.tv_sec - time_prev.tv_sec) * 1000 + (time_now.tv_usec
			- time_prev.tv_usec) / 1000);
}

int	alive(t_philo *philo)
{
	struct timeval	time_now;

	sem_wait(philo->data->write);
	gettimeofday(&time_now, NULL);
	if ((time_now.tv_sec - philo->last_meal.tv_sec) * 1000 + (time_now.tv_usec
			- philo->last_meal.tv_usec)
		/ 1000 >= (long)philo->data->time_to_die)
	{
		printf("%.4zu %d %s\n", gettime(philo->data->start_time), philo->id,
			"died");
		return (0);
	}
	sem_post(philo->data->write);
	return (1);
}
