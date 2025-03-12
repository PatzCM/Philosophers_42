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

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				eat_count;
	int				last_eat;
	int				status;
	pthread_t		thread;
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
	int				philo_done;
	int				philo_done_count;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	dead;
	pthread_mutex_t	full;
	pthread_mutex_t	done;
	pthread_mutex_t	done_max;
	t_philo			*philos;
}					t_data;

// Functions //
// Utils //

long		ft_atol(char *str);


#endif
