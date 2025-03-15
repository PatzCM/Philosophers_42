#include "philosophers.h"

long	ft_atol(char *str)
{
	long i;
	int sign;
	long res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
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

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = 0;
	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_msg(t_data *data, t_philo *phil, char *status)
{
	if (data->philo_dead == ALIVE)
	{
		pthread_mutex_lock(&data->print);
		printf("%ld %d %s\n", get_current_time() - data->start_time, phil->id, status);
		pthread_mutex_unlock(&data->print);
	}

	else if (p_strcmp(status, "died") == 0)
	{
		pthread_mutex_lock(&data->print);
		printf("%ld %d %s\n", get_current_time() - data->start_time, phil->id, status);
		pthread_mutex_unlock(&data->print);
	}
}

int		p_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
