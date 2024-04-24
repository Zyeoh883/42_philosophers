/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:33:10 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 19:04:06 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_FORMAT \
	"Format: <Num_philosophers> <Time_to_die> <Time_to_eat> \
<Time_to_sleep> (optional) Num_times_each_philosophers_must_eat\n"
# define ERROR_INPUT_TYPE "Inputs must be a positive non zero int type\n"

# define MAX_PHILO 200

typedef struct s_philo
{
	pthread_t		thread;
	pid_t			pid;
	int				meals;
	int				id;
	sem_t			*forks;
	struct timeval	last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_flag;
	int				maxnum_of_meals;
	sem_t			*write;
	struct timeval	start_time;
}					t_data;

void				kill_exit(t_data data, t_philo *philo);
void				ft_usleep(size_t duration);
void				*monitor(void *arg);

long				ft_atoi(const char *str);
int					make_semaphore(sem_t **sem, char *name, int count);
int					init_semaphores(t_data *data, sem_t **forks);
int					init_philo(t_data *data, sem_t *forks, t_philo *philo);
int					initialize(int ac, char **av, t_data *data);

int					routine(t_philo *philo);
int					spawn_threads(t_data *data, t_philo *philo);

int					ft_is_all_digits(char *str);
int					parse(int ac, char **av);
size_t				gettime(struct timeval time_prev);
int					alive(t_philo *philo);
int					join_threads(t_data *data);
int					destroy_mutexes(t_data *data, pthread_mutex_t *mutex);

void				print_message(t_philo *philo, char *str);
void				clean_sem(t_philo *philo);
#endif