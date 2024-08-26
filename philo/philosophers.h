/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:43:37 by marvin            #+#    #+#             */
/*   Updated: 2024/08/26 11:56:20 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdint.h>

# define MAX_PHILO 200

typedef struct s_timer
{
	struct timeval	timer;
	size_t			start_time;
}					t_timer;

typedef struct s_databank
{
	size_t			init_time;
	size_t			deathdelay;
	size_t			eatdelay;
	size_t			sleepdelay;
	int				sated_counter;
	int				num_of_phils;
	int				max_meals;
}					t_databank;

typedef struct s_philo
{
	pthread_t		thread;
	int				tid;
	size_t			timestamp_last_meal;
	int				food_consumed;
	int				sated;
	int				*confirmed_death;
	pthread_mutex_t	*right_f;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*lock_messaging;
	pthread_mutex_t	*lock_eating;
	t_databank		*databank;
}					t_philo;

typedef struct s_discussion
{
	int				death_flag;
	pthread_mutex_t	lock_eating;
	pthread_mutex_t	lock_messaging;
	t_philo			philos[MAX_PHILO];
}					t_discussion;

int					init_program(t_discussion *program, t_databank *databank);
void				init_databank(t_databank *databank, char **argv, int argc);
int					check_args(int argc, char **argv);
void				*philo_routine(void *philos);
size_t				ms_timer(struct timeval time);
size_t				timer_start(void);
void				improved_sleep(size_t time_delay, t_philo *philosopher);
void				init_philo(t_philo *philos, int id, t_discussion *program,
						pthread_mutex_t *forks);
void				print_function(t_philo *philo, char *string,
						size_t current_ms);
int					check_death_flag(t_philo *philo);
void				*guard_routine(void *all_philos);
void				cleanup_func(t_discussion *program, t_databank *data,
						pthread_t *watchguard, int creation_result);
int					check_starvation(t_philo *watchguard);

/*-----------------util functions--------------------*/
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_issign(int c);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t size);

#endif