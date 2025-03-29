/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:23:42 by palexand          #+#    #+#             */
/*   Updated: 2025/03/28 18:57:29 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*============================================================================#
#                                 libraries                                   #
#============================================================================*/

#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


/*============================================================================#
#                                 macros                                      #
#============================================================================*/

#define MAX_PHILO 200

# define ALIVE 0
# define DEAD  1
# define FULL  2
# define ERROR_MALLOC 3
# define ERROR_PARSING 4

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DEAD_MSG "died"


/*============================================================================#
#                                 structs                                     #
#============================================================================*/

typedef struct s_data
{
	int				nb_philos;
	long long				start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_eat;
	int				nb_eat_counter;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	data;
	struct s_philo			*philo;
} t_data;

typedef struct s_philo
{
	int				id;
	int				eat_counter;
	int				full;
	long long				last_eat;
	int				status;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		threads;
	t_data			*data_struct;
} t_philo;

/*============================================================================#
#                              functions                                     #
#============================================================================*/

int	p_isdigit(char *str);
int	p_strcmp(const char *s1, const char *s2);
long	ft_atol(char *str);
int	p_parsing(int ac, char **av);
int	data_init(t_data *data, char **av, int ac);
void	philo_mutex(t_data *data);
void	philo_init(t_data *data);
int philo_thread(t_data *data);
void	*philo_routine(void *philo);
long long	now(void);
void	print_msg(t_data *data, char *status);
void	finalize(t_data *data);
void	philo_eat(t_philo *philo);
void	philo_monitor(t_data *data);
void sleep_time(long long time);

#endif
