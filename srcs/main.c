/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:39:00 by fmustin           #+#    #+#             */
/*   Updated: 2022/01/18 15:39:01 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/main.h"

int	ft_clear(t_data *data, int i)
{
	free(data->philos);
	data->philos = NULL;
	if (i > 0)
	{
		free(data->forks);
		data->forks = NULL;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		error;

	if (argc < 5 || argc > 6)
		return (printf("Wrong number of arguments"));
	error = data_init(argc, argv, &data);
	if (error == 1)
		return (printf("Error in arguments"));
	if (error == 2)
		return (0);
	if (error == 3)
		return (printf("Error while mallocating philos\n")
			&& ft_clear(&data, 0));
	if (error == 4)
		return (printf("Error while mallocating forks\n")
			&& ft_clear(&data, 1));
	if (error == 5)
		return (printf("Error while initializating mutex\n")
			&& ft_clear(&data, 1));
	philo_creator(&data);
	return (ft_clear(&data, 1));
}
