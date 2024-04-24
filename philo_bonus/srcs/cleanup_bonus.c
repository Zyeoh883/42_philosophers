/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 17:26:08 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 19:07:58 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_sem(t_philo *philo)
{
	sem_close(philo->forks);
	sem_close(philo->data->write);
	sem_unlink("forks");
	sem_unlink("write");
}
