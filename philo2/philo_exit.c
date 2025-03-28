/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:48:35 by palexand          #+#    #+#             */
/*   Updated: 2025/03/28 18:57:03 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(t_data *data, char *status)
{
	if (data->philo->status == ALIVE)
	{
		pthread_mutex_lock(&data->print);
		printf("%lld %d %s\n", now() - data->start_time, data->philo->id, status);
		pthread_mutex_unlock(&data->print);
	}
}

void	finalize(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_join(data->philo[i].threads, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->data);
	free(data->forks);
	free(data->philo);
}

