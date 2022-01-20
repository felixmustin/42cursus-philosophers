/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:38:52 by fmustin           #+#    #+#             */
/*   Updated: 2022/01/18 15:54:28 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

void	init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		data->philos[i].pos = i + 1;
		data->philos[i].lfork = i;
		data->philos[i].rfork = ((i + 1) % data->nbr_philo);
		data->philos[i].data = data;
	}
}

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(*(data->forks)) * data->nbr_philo);
	if (!(data->forks))
		return (4);
	i = -1;
	while (++i < data->nbr_philo)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (5);
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (5);
	if (pthread_mutex_init(&(data->lock), NULL))
		return (5);
	return (0);
}

int	data_init(int argc, char **args, t_data *data)
{
	data->nbr_philo = ft_atoi(args[1]);
	data->time_to_die = ft_atoi(args[2]);
	data->time_to_eat = ft_atoi(args[3]);
	data->time_to_sleep = ft_atoi(args[4]);
	if (check_args(data, args, argc))
		return (1);
	if (one_philo(data))
		return (2);
	data->dead = 0;
	data->ate = 0;
	data->all_eat = 0;
	data->mutex_lock = 0;
	data->forks = NULL;
	data->philos = NULL;
	data->philos = ft_calloc(sizeof(*(data->philos)), data->nbr_philo);
	if (!data->philos)
		return (3);
	init_philos(data);
	return (init_mutex(data));
}

int	one_philo(t_data *data)
{
	if (data->nbr_philo == 1)
	{
		usleep(data->time_to_sleep * 1000);
		printf("%d ms 1 died\n", data->time_to_sleep);
		return (1);
	}
	return (0);
}

int	check_args(t_data *data, char **args, int argc)
{
	if (argc == 6)
	{
		if (ft_atoi(args[5]) > 0)
			data->eat_count = ft_atoi(args[5]);
		else
			return (1);
	}
	else
		data->eat_count = -1;
	if (data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0 || data->nbr_philo <= 0)
		return (1);
	return (0);
}
