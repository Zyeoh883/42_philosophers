/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:07:31 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 18:58:22 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	make_semaphore(sem_t **sem, char *name, int count)
{
	sem_t	*new_sem;

	sem_unlink(name);
	new_sem = sem_open(name, O_CREAT | O_EXCL, 0644, count);
	if (new_sem == SEM_FAILED)
	{
		perror("sem_open");
		return (0);
	}
	*sem = new_sem;
	return (1);
}

int	init_semaphores(t_data *data, sem_t **forks)
{
	if (!make_semaphore(&data->write, "write", 1))
		return (0);
	if (!make_semaphore(forks, "forks", data->num_philo))
		return (0);
	return (1);
}

int	init_philo(t_data *data, sem_t *forks, t_philo *philo)
{
	int	n;

	n = -1;
	while (++n < data->num_philo)
	{
		memset(&philo[n], 0, sizeof(t_philo));
		philo[n].data = data;
		philo[n].id = n;
		philo[n].forks = forks;
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
