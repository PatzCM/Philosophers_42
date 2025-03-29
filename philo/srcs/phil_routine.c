/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 20:22:03 by palexand          #+#    #+#             */
/*   Updated: 2025/03/19 16:55:23 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_msg(philo->data, philo, FORK);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&philo->data->status);
	print_msg(philo->data, philo, FORK);
	print_msg(philo->data, philo, EAT);
	pthread_mutex_unlock(&philo->data->status);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->status);
	philo->last_eat = get_current_time();
	if (philo->eat_count < philo->data->must_eat_count)
		philo->eat_count++;
	pthread_mutex_unlock(&philo->data->status);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	*philo_routine(void *phil_arg)
{
	t_philo	*philo;

	philo = (t_philo *)phil_arg;
	pthread_mutex_lock(&philo->data->status);
	philo->last_eat = philo->data->start_time;
	pthread_mutex_unlock(&philo->data->status);
	if (philo->data->philo_count == 1)
	{
		print_msg(philo->data, philo, FORK);
		ft_usleep(philo->data->time_to_die);
		return (NULL);
	}
	if (philo->id % 2 != 0)
	{
		print_msg(philo->data, philo, THINK);
		ft_usleep(100);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->status);
		if (philo->data->philo_dead != ALIVE)
		{
			pthread_mutex_unlock(&philo->data->status);
			break ;
		}
		pthread_mutex_unlock(&philo->data->status);
		eat(philo);
		p_sleep(philo);
		pthread_mutex_lock(&philo->data->status);
		print_msg(philo->data, philo, THINK);
		pthread_mutex_unlock(&philo->data->status);
	}
	return (NULL);
}

void	philo_monitor(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo_status(&data->philo[i], data) != ALIVE)
			break ;
		i++;
		if (i == data->philo_count)
			i = 0;

	}
	if (data->philo_dead == DEAD)
		print_msg(data, &data->philo[i], DIED);
}

void	p_sleep(t_philo *philo)
{
	print_msg(philo->data, philo, SLEEP);
	if (philo->data->time_to_sleep > philo->data->time_to_die)
		ft_usleep(philo->data->time_to_die);
	else
		ft_usleep(philo->data->time_to_sleep);
}
