/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: palexand <palexand@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 22:46:25 by palexand          #+#    #+#             */
/*   Updated: 2025/03/15 22:46:26 by palexand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philosophers.h"

long	ft_atol(char *str)
{
	long	i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

void	print_msg(t_data *data, t_philo *phil, char *status)
{
	if (data->philo_dead == ALIVE)
	{
		pthread_mutex_lock(&data->print);
		printf("%ld %d %s\n", get_current_time() - \
				data->start_time, phil->id, status);
		pthread_mutex_unlock(&data->print);
	}
	else if (p_strcmp(status, "died") == 0)
	{
		pthread_mutex_lock(&data->print);
		printf("%ld %d %s\n", get_current_time() - \
				data->start_time, phil->id, status);
		pthread_mutex_unlock(&data->print);
	}
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

int	p_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
