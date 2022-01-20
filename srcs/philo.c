/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:41:36 by fmustin           #+#    #+#             */
/*   Updated: 2022/01/18 15:41:54 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	philo_creator(t_data *data)
{
	int			i;
	t_philo		*philo;

	philo = data->philos;
	gettimeofday(&(data->start), NULL);
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&(philo[i].thread), NULL,
				&philo_routine, &(philo[i])) != 0)
			return (1);
		usleep(100);
		i++;
	}
	if (philo_check_death(data, philo))
	{
		data->mutex_lock = 1;
		pthread_mutex_unlock(&philo->data->lock);
	}
	philo_check_exit(data, philo);
	return (0);
}

void	*philo_routine(void *vargp)
{
	t_philo	*philo;

	philo = (t_philo *)vargp;
	if (philo->pos % 2 == 0)
		usleep(500);
	while (1)
	{
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (philo_think(philo))
			break ;
	}
	pthread_mutex_unlock(&philo->data->lock);
	return ((void *) 0);
}

int	philo_check_death(t_data *data, t_philo *philo)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nbr_philo)
		{
			pthread_mutex_lock(&data->lock);
			if ((timestamp(philo) - philo[i].time_ate) >= data->time_to_die)
			{
				philo_display(philo, " died\n");
				philo->data->dead = 1;
				return (1);
			}
			if (data->eat_count > 0)
			{
				if (data->ate >= (data->nbr_philo * data->eat_count))
				{
					philo->data->all_eat = 1;
					return (1);
				}
			}
			pthread_mutex_unlock(&data->lock);
		}
	}
}

int	simulation_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->dead || philo->data->all_eat)
		return (1);
	pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

void	philo_check_exit(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->nbr_philo)
		pthread_join(philos[i].thread, NULL);
	if (data->all_eat)
		printf("Everyone has eaten\n");
	i = -1;
	while (++i < data->nbr_philo)
		pthread_mutex_destroy(&(data->forks[i]));
	pthread_mutex_destroy(&(data->writing));
	pthread_mutex_destroy(&(data->lock));
}
