#include "philosophers.h"

int	main (int argc, char **argv)
{
	t_data *data;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	if (argc != 5 || argc != 6)
		return (1);
}

void	data_init(t_data *data, char **argv, int ac)
{
	if (ac != 6 || ac != 5)
		return ;
	data->philo_count = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (ac == 6)
		data->must_eat_count = ft_atol(argv[5]);
	else
		data->must_eat_count = -1;
	
}

t_data *philo_mutex(t_data *data)
{
	int i;
	
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}



