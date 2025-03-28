/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:34:56 by palexand          #+#    #+#             */
/*   Updated: 2025/03/28 18:57:34 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_data *data, char **av, int ac)
{
	data->nb_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	data->nb_eat = -1;
	if (ac == 6)
		data->nb_eat = ft_atol(av[5]);
	if (data->nb_philos > MAX_PHILO)
		return (ERROR_PARSING);
	if (data->nb_philos < 1 || data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60 || (ac == 6 && data->nb_eat < 1))
		return (ERROR_PARSING);
	data->start_time = 0;
	philo_init(data);
	return (0);
}

void	philo_init(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	data->philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (!data->forks || !data->philo)	
		return (printf("Error: malloc\n"), exit(1));
	i = 0;
	while (i < data->nb_philos)
	{
		data->philo[i].id = i + 1;
		data->philo[i].last_eat = 0;
		data->philo[i].eat_counter = 0;
		data->philo[i].status = ALIVE;
		data->philo[i].full = 0;
		i++;
	}
}


void	philo_mutex(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	data->philo[0].right_fork = &data->forks[0];
	if (data->nb_philos == 1)
		return ;
	data->philo[0].left_fork = &data->forks[data->nb_philos - 1];
	while (++i < data->nb_philos)
	{
		if (data->philo[i].id % 2 == 0 && data->nb_philos != 2)
		{
			data->philo[i].right_fork = &data->forks[i];
			data->philo[i].left_fork = &data->forks[i - 1];
		}
		else
		{
			data->philo[i].right_fork = &data->forks[i - 1];
			data->philo[i].left_fork = &data->forks[i];
		}
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->data, NULL);
}

