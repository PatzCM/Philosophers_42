/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:50:38 by palexand          #+#    #+#             */
/*   Updated: 2025/03/15 22:50:38 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;	

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	if (argc != 5 && argc != 6)
		return (1);
	data_init(data, argv, argc);
	philo_init(data);
	philo_mutex(data);
	if (philo_thread(data) != 0)
		return (1);
	p_free(data);
}

int	philo_thread(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->status);
	while (i < data->philo_count)
	{
		if (pthread_create(&data->thread[i], NULL,
				&philo_routine, &data->philo[i]) != 0)
			return (1);
		i++;
	}
	data->start_time = get_current_time();
	pthread_mutex_unlock(&data->status);
	ft_usleep(data->time_to_eat - 10);
	philo_monitor(data);
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_join(data->thread[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}
// the philosophers routine function should be like this:
// should initialize the philo to eat, sleep and think
// should check if the philosopher is dead
// repeat

int	philo_status(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	if (get_current_time() - philo->last_eat > (size_t)data->time_to_die)
	{
		data->philo_dead = DEAD;
		return (DEAD);
	}
	else if (philo->eat_count == data->must_eat_count && philo->full == 0)
	{
		data->philo_full++;
		philo->full = 1;
	}
	if (data->philo_full == data->philo_count)
		data->philo_dead = FULL;
	i = data->philo_dead;
	return (i);
}
