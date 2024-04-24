/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:46:57 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 17:08:48 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->death != 1)
		printf("%.4zu %d %s\n", gettime(philo->data->start_time), philo->id,
			str);
	pthread_mutex_unlock(&philo->data->write);
}

void	ft_usleep(size_t duration)
{
	struct timeval	start_time;
	struct timeval	time_now;

	gettimeofday(&start_time, NULL);
	time_now = start_time;
	while ((time_now.tv_sec - start_time.tv_sec) * 1000 + (time_now.tv_usec
			- start_time.tv_usec) / 1000 < (long)duration)
	{
		usleep(250);
		gettimeofday(&time_now, NULL);
	}
}

int	eating(t_philo *philo)
{
	print_message(philo, "is thinking");
	pthread_mutex_lock(philo->l_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->philo_lock);
	philo->meals++;
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->philo_lock);
	ft_usleep(philo->data->time_to_eat);
	print_message(philo, "is sleeping");
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (philo->data->death == 1)
		return (0);
	ft_usleep(philo->data->time_to_sleep);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(3000);
	while (eating(philo))
		;
	return (NULL);
}

int	spawn_threads(t_data *data, t_philo *philo)
{
	int	n;

	gettimeofday(&data->start_time, NULL);
	n = -1;
	while (++n < data->num_philo)
	{
		philo[n].last_meal = philo->data->start_time;
		if (pthread_create(&philo[n].thread, NULL, routine, &philo[n]) != 0)
			return (0);
	}
	return (1);
}

// pthread_detach(philo->thread);

// static void	calculate_time(t_philo *philo, int sleeping)
// {
// 	philo->last_meal.tv_sec += philo->data->time_to_eat * 1000;
// 	if (philo->last_meal.tv_usec >= 100000)
// 	{
// 		philo->last_meal.tv_sec++;
// 		philo->last_meal.tv_usec -= 100000;
// 	}
// 	if (sleeping)
// 	{
// 		philo->last_meal.tv_sec += philo->data->time_to_eat * 1000;
// 		if (philo->last_meal.tv_usec >= 100000)
// 		{
// 			philo->last_meal.tv_sec++;
// 			philo->last_meal.tv_usec -= 100000;
// 		}
// 	}
// }

// void	get_last_ate(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->philo_lock);
// 	philo->last_meal = gettime_abs();
// 	philo->meals++;
// 	pthread_mutex_unlock(&philo->philo_lock);
// }

// void	sleeping(t_philo *philo)
// {
// 	pthread_mutex_unlock(philo->l_fork);
// 	pthread_mutex_unlock(philo->r_fork);
// 	usleep(philo->data->time_to_sleep * 1000);
// }