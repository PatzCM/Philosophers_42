/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:17:51 by palexand          #+#    #+#             */
/*   Updated: 2025/03/28 18:47:46 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *ph)
{
	t_philo	*philo;
	printf("philo %d\n", philo->id);

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->data_struct->data);
	pthread_mutex_unlock(&philo->data_struct->data);
	philo->last_eat = philo->data_struct->start_time;
	if (philo->data_struct->nb_philos == 1)
			// function_solo
	if (philo->id % 2 == 0)
	{
			print_msg(philo->data_struct, THINK);
			usleep(100);
	}	
	if (philo->status == ALIVE)
	{
		philo_eat(philo);
		/*philo_sleep(ph);*/
		/*philo_think(ph);*/
	}
	return (NULL);
}

int	philo_status(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&data->data);
	if (now() - philo->last_eat > philo->data_struct->time_to_die)
	{
		philo->status = DEAD;
		printf("%lld %d %s\n", now() - philo->data_struct->start_time, philo->id, DEAD_MSG);
		pthread_mutex_unlock(&data->data);
		return (1);
	}
	else if (philo->data_struct->nb_eat != -1 && philo->eat_counter >= philo->data_struct->nb_eat)
	{
		philo->status = FULL;
		philo->full = 1;
		pthread_mutex_unlock(&data->data);
		return (1);
	}
	pthread_mutex_unlock(&data->data);
	return (0);
}

void	philo_monitor(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (i == data->nb_philos)
			i = 0;
		if (philo_status(&data->philo[i], data) == 1)
			break ;
		i++;
		usleep(5);
	}
	finalize(data);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo->data_struct, FORK);
	pthread_mutex_lock(philo->left_fork);
	print_msg(philo->data_struct, FORK);
	print_msg(philo->data_struct, EAT);
	philo->last_eat = now();
	philo->eat_counter++;
	usleep(philo->data_struct->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
