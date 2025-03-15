/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 22:07:28 by palexand          #+#    #+#             */
/*   Updated: 2025/03/10 22:22:47 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/*============================================================================#
#                                 macros                                      #
#============================================================================*/

# define ALIVE 1
# define DEAD 0
# define FULL 2
# define ERROR_MALLOC 3
# define PARSING_ERROR 4

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

/*============================================================================#
#                                 libraries                                   #
#============================================================================*/


# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>

/*============================================================================#
#                                 structs                                     #
#============================================================================*/


typedef struct s_philo
{
	int							id;
	int							eat_count;
	size_t					last_eat;
	int							full;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}					t_philo; 

typedef struct s_data
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				philo_dead;
	int				philo_full;
	size_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	status;
	pthread_t		*thread;
	t_philo			*philo;
}					t_data;


/*============================================================================#
#                              functions                                     #
#============================================================================*/

int	allocate_memory(t_data *data, int	phil_nbr);

long		ft_atol(char *str);
void	philo_init(t_data *data);
int	data_init(t_data *data, char **argv, int ac);
size_t	get_current_time(void);
void	ft_usleep(size_t milliseconds);
void	*philo_routine(void *phil_arg);
int philo_status(t_philo *philo, t_data *data);
void	philo_monitor(t_data *data);
int philo_thread(t_data *data);
int		p_strcmp(const char *s1, const char *s2);
void	print_msg(t_data *data, t_philo *phil, char *status);
void	eat(t_philo *philo);
void	philo_mutex(t_data *data);
void	p_sleep(t_philo *philo);
void	p_free(t_data *data);


#endif
