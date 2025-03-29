/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:50:38 by palexand          #+#    #+#             */
/*   Updated: 2025/03/19 16:45:12 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;	
	int		error;
	
	/*data = malloc(sizeof(t_data));*/
	/*if (!data)*/
	/*	return (ERROR_MALLOC);*/
	error = 0;
	error = p_parsing(argc, argv);
	if (error != 0)
	{
		p_error(error);
		/*free(data);*/
		return (PARSING_ERROR);
	}
	data_init(&data, argv, argc);
	philo_init(&data);
	philo_mutex(&data);
	philo_thread(&data);
	p_free(&data);
}

int	p_parsing(int ac, char **av)
{
	int	i;

	i = 1;
	if (ac < 5 || ac > 6)
		return (-1);
	if (av[1][0] == '\0' || av[2][0] == '\0' || av[3][0] == '\0' || av[4][0] == '\0')
		return (-1);
	if (ft_atol(av[1]) > 200)
		return (-3);
	while (av[i])
	{
		if (p_isdigit(av[i]) == 1 || ft_atol(av[i]) < 0)
			return (-2);
		if (ft_atol(av[i]) > INT_MAX || ft_atol(av[i]) < INT_MIN)
			return (-4);
		i++;
	}
	return (0);
}

int	philo_thread(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->status);
	while (++i < data->philo_count)
	{
		if (pthread_create(&data->thread[i], NULL,
				&philo_routine, &data->philo[i]) != 0)
			return (1);
	}
	data->start_time = get_current_time();
	pthread_mutex_unlock(&data->status);
	ft_usleep(data->time_to_die - 10);
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
	pthread_mutex_lock(&data->status);
	if (get_current_time() - data->philo->last_eat > (size_t)data->time_to_die)
	{
		/*pthread_mutex_lock(&data->status);*/
		data->philo_dead = DEAD;
		pthread_mutex_unlock(&data->status);
		return (DEAD);
	}
	else if (philo->eat_count == data->must_eat_count && philo->full == 0)
	{
		/*pthread_mutex_lock(&data->status);*/
		/*printf("philo->eat_count: %d\n", philo->eat_count);*/
		data->philo_full++;
		philo->full = 1;
	}

	if (data->philo_full == data->philo_count)
		data->philo_dead = FULL;
	i = data->philo_dead;
	pthread_mutex_unlock(&data->status);
	return (i);
}
