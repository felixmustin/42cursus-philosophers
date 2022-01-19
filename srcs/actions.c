/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:37:57 by fmustin           #+#    #+#             */
/*   Updated: 2022/01/18 15:38:45 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	philo_think(t_philo *philo)
{
	if (simulation_stop(philo))
		return (1);
	philo_display(philo, " is thinking\n");
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (simulation_stop(philo))
		return (1);
	philo_display(philo, " is sleeping\n");
	ft_usleep(philo, philo->data->time_to_sleep);
	return (0);
}

int	philo_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->lfork]);
	philo_display(philo, " has taken a fork\n");
	pthread_mutex_lock(&philo->data->forks[philo->rfork]);
	philo_display(philo, " has taken a fork\n");
	return (1);
}

int	philo_eat(t_philo *philo)
{
	if (simulation_stop(philo))
		return (1);
	philo_fork(philo);
	pthread_mutex_lock(&philo->data->lock);
	philo_display(philo, " is eating\n");
	philo->time_ate = timestamp(philo);
	pthread_mutex_unlock(&philo->data->lock);
	ft_usleep(philo, philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->lock);
	philo->data->ate += 1;
	pthread_mutex_unlock(&philo->data->lock);
	pthread_mutex_unlock(&philo->data->forks[philo->lfork]);
	pthread_mutex_unlock(&philo->data->forks[philo->rfork]);
	return (0);
}
