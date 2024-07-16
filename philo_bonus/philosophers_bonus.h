/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleibeng <mleibeng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:43:37 by marvin            #+#    #+#             */
/*   Updated: 2024/01/28 15:15:32 by mleibeng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	int				num_of_phils;
	int				max_meals;
	int				sated_counter;
	sem_t			*lock_counter;
	sem_t			*exit_process;
	sem_t			*lock_eating;
	sem_t			*lock_messaging;
}					t_databank;

typedef struct s_philo
{
	pid_t			pid;
	int				ident;
	size_t			timestamp_last_meal;
	int				food_consumed;
	int				sated;
	int				confirmed_death;
	t_databank		*databank;
}					t_philo;

/*functions that are ok for now*/
int					init_program(t_philo *philos, t_databank *databank);
int					init_databank(t_databank *databank, char **argv, int argc);
int					check_args(int argc, char **argv);
size_t				ms_timer(struct timeval time);
size_t				timer_start(void);
void				improved_sleep(size_t time_delay);
void				print_function(t_philo *philo, char *string);
void				philo_routine(t_philo *philos, sem_t *forks);
/*functions that need change*/
void				*check_death_flag(void *phil);
void				cleanup_func(t_philo *philo, sem_t *forks);
void				check_starvation(t_philo *watchguard);

/*-----------------util functions--------------------*/
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
int					ft_issign(int c);
int					ft_isdigit(int c);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t size);

#endif