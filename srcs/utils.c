/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:42:25 by fmustin           #+#    #+#             */
/*   Updated: 2022/01/18 15:42:57 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

long int	timestamp(t_philo *philo)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000))
		- ((philo->data->start.tv_sec * 1000)
			+ (philo->data->start.tv_usec / 1000)));
}

void	ft_usleep(t_philo *philo, useconds_t time)
{
	long int	time_check;

	time_check = timestamp(philo);
	while (1)
	{
		if ((timestamp(philo) - time_check) >= time)
			break ;
		usleep(philo->data->nbr_philo * 2);
	}
}

void	philo_display(t_philo *philo, char *str)
{
	long int	time;

	if (philo->data->mutex_lock)
		return ;
	pthread_mutex_lock(&philo->data->writing);
	time = timestamp(philo);
	printf("%lu ms %d%s", time, philo->pos, str);
	pthread_mutex_unlock(&philo->data->writing);
}

int	ft_atoi(const char *str)
{
	int					signe;
	unsigned long int	nb;

	signe = 1;
	nb = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 43 || *str == 45 || (*str >= 48 && *str <= 57))
	{
		if (*str == 45)
			signe = -1;
	}
	else
		return (0);
	if (!(*str >= 48 && *str <= 57))
		str++;
	while (*str >= 48 && *str <= 57 && *str != '\0')
	{
		nb = nb * 10 + (*str++ - '0');
		if (nb > 2147483647 && signe == 1)
			return (-1);
		if (nb > 2147483648 && signe == -1)
			return (0);
	}
	return (signe * nb);
}
