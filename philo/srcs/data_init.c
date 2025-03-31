/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 18:22:26 by palexand          #+#    #+#             */
/*   Updated: 2025/03/15 22:29:43 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../incs/philosophers.h"

int	data_init(t_data *data, char **argv, int ac)
{
	data->philo_count = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->philo_dead = ALIVE;
	data->philo_full = 0;
	if (ac == 6)
		data->must_eat_count = ft_atol(argv[5]);
	else
		data->must_eat_count = -1;
	if (allocate_memory(data, data->philo_count) != 0)
		return (printf("Error: malloc\n"));
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->status, NULL);
	data->start_time = 0;
	return (0);
}

int	allocate_memory(t_data *data, int phil_nbr)
{
	data->thread = malloc(sizeof(pthread_t) * phil_nbr);
	if (data->thread == NULL)
		return (ERROR_MALLOC);
	data->philo = malloc(sizeof(t_philo) * phil_nbr);
	if (data->philo == NULL)
		return (free(data->thread), ERROR_MALLOC);
	data->forks = malloc(sizeof(pthread_mutex_t) * phil_nbr);
	if (data->forks == NULL)
		return (free(data->thread), free(data->philo), ERROR_MALLOC);
	return (0);
}

void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->philo_count)
	{
		philo[i].id = i + 1;
		philo[i].eat_count = 0;
		philo[i].data = data;
		philo[i].last_eat = 0;
		philo[i].full = 0;
		i++;
	}
}

void	philo_mutex(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philo;
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_init(&data->forks[i], NULL);
	i = 0;
	philo[0].right_fork = &data->forks[0];
	if (data->philo_count == 1)
		return ;
	philo[0].left_fork = &data->forks[data->philo_count - 1];
	while (++i < data->philo_count)
	{
		if (philo[i].id % 2 == 0 && data->philo_count != 2)
		{
			philo[i].right_fork = &data->forks[i];
			philo[i].left_fork = &data->forks[i - 1];
		}
		else
		{
			philo[i].right_fork = &data->forks[i - 1];
			philo[i].left_fork = &data->forks[i];
		}
	}
}
