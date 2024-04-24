/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:27:49 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 19:07:28 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_exit(t_data data, t_philo *philo)
{
	int	eaten;
	int	status;
	int	n;

	eaten = 0;
	while (eaten < data.num_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			n = -1;
			while (++n < data.num_philo)
				kill(philo[n].pid, SIGTERM);
			return ;
		}
		else if (WEXITSTATUS(status) == 0)
			eaten++;
	}
}

void	*monitor(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (alive(philo))
		usleep(5000);
	exit(1);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	philo[MAX_PHILO];
	sem_t	*forks;

	if (!parse(ac, av))
		return (EXIT_FAILURE);
	if (!initialize(ac, av, &data))
	{
		printf("init error\n");
		return (EXIT_FAILURE);
	}
	if (!init_semaphores(&data, &forks))
		return (EXIT_FAILURE);
	if (!init_philo(&data, forks, philo))
		return (EXIT_FAILURE);
	if (!spawn_threads(&data, philo))
		return (0);
	kill_exit(data, philo);
	clean_sem(philo);
	return (0);
}
