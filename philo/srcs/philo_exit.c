/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:23:01 by palexand          #+#    #+#             */
/*   Updated: 2025/03/19 16:45:21 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

void	p_error(int error)
{
	if (error == -1)
		printf("Error: Invalid number of arguments\n");
	if (error == -2)
		printf("Error: Invalid, non-digit or negative number found\n");
	if (error == -3)
		printf("Error: Number of Philosophers must be less than 200\n");
	if (error == -4)
		printf("Error: Argument out of INT range\n");
}

void	p_free(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->status);
	free(data->thread);
	free(data->philo);
	free(data->forks);
	free(data);
}
