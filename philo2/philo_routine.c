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

	philo = (t_philo *)ph;
	pthread_mutex_lock(&philo->data_struct->data);
	pthread_mutex_unlock(&philo->data_struct->data);
	philo->last_eat = philo->data_struct->start_time;
	printf("philo %d\n", philo->id);
	if (philo->data_struct->nb_philos == 1)
	{
		print_msg(philo->data_struct, FORK);
		sleep_time(philo->data_struct->time_to_die);
		print_msg(philo->data_struct, DEAD_MSG);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
			print_msg(philo->data_struct, THINK);
			usleep(100);
	}	
	while (philo->status == ALIVE)
	{
		philo_eat(philo);
		print_msg(philo->data_struct, SLEEP);
		sleep_time(philo->data_struct->time_to_sleep);
		print_msg(philo->data_struct, THINK);
	}
	return (NULL);
}

int	philo_status(t_philo *philo, t_data *data)
{
	int i;
	/*pthread_mutex_lock(&data->data);*/
	i = 0;
	if (now() - philo->last_eat >= data->time_to_die)
	{
		philo->status = DEAD;
		/*printf("%lld %d %s\n", now() - data->start_time, data->philo->id, DEAD_MSG);*/
		print_msg(data, DEAD_MSG);
		/*pthread_mutex_unlock(&data->data);*/
		return (DEAD);
	}
	else if (philo->data_struct->nb_eat != -1 && philo->eat_counter >= philo->data_struct->nb_eat && philo->full == 0)
	{
		philo->data_struct->nb_eat_counter++;
		philo->full = 1;
	}
	if (philo->data_struct->nb_eat_counter == philo->data_struct->nb_philos)
		philo->status = FULL;
	i = philo->status;
	/*pthread_mutex_unlock(&data->data);*/
	/*pthread_mutex_unlock(&data->data);*/
	return (i);
}

void	philo_monitor(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			if (philo_status(&data->philo[i], data) != ALIVE)
				break ;
		}
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
	pthread_mutex_lock(&philo->data_struct->data);
	philo->last_eat = now();
	philo->eat_counter++;
	sleep_time(philo->data_struct->time_to_eat);
	pthread_mutex_unlock(&philo->data_struct->data);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
