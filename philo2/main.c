/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:30:21 by palexand          #+#    #+#             */
/*   Updated: 2025/03/28 18:56:14 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;
	int		error;

	error = p_parsing(ac, av);
	error = data_init(&data, av, ac);
	if (error != 0)
		return (ERROR_PARSING);
	philo_mutex(&data);
	if (philo_thread(&data) != 0)
		return (1);
}

int philo_thread(t_data *data)
{
	int i;

	i = -1;
	pthread_mutex_lock(&data->data);
	while (++i < data->nb_philos)
	{
		if (pthread_create(&data->philo[i].threads, NULL, philo_routine, &data->philo[i]) != 0)
			return (1);
	}
	data->start_time = now();
	pthread_mutex_unlock(&data->data);
	philo_monitor(data);
	return (0);
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


