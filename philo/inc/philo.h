/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 15:33:10 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/09 16:34:16 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
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
	int				meals;
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	philo_lock;
	struct s_data	*data;
	struct timeval	last_meal;
}					t_philo;

typedef struct s_data
{
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meal_flag;
	int				maxnum_of_meals;
	int				death;
	pthread_mutex_t	write;
	struct timeval	start_time;
}					t_data;

void				ft_usleep(size_t duration);
void				monitor(t_data *data, t_philo *philo);
int					threading(t_data *data);

long				ft_atoi(const char *str);
int					init_mutex_array(pthread_mutex_t *result, int len);
int					init_mutex(t_data *data, pthread_mutex_t *mutex);
int					init_philo(t_data *data, pthread_mutex_t *mutex,
						t_philo *philo);
int					initialize(int ac, char **av, t_data *data);

void				take_forks(t_philo *philo);
void				place_forks(t_philo *philo);
void				*routine(void *arg);
int					spawn_threads(t_data *data, t_philo *philo);

int					ft_is_all_digits(char *str);
int					parse(int ac, char **av);
size_t				gettime(struct timeval time_prev);
int					alive(t_philo *philo);
void				multi_mutex_unlock(t_philo *philo);
int					join_threads(t_data *data);
int					destroy_mutexes(t_data *data, pthread_mutex_t *mutex);

void				*death_routine(void *arg);
void				print_message(t_philo *philo, char *str);

#endif