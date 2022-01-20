/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmustin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:47:43 by fmustin           #+#    #+#             */
/*   Updated: 2022/01/18 16:51:23 by fmustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	int				pos;
	int				lfork;
	int				rfork;
	long int		time_ate;
	struct s_data	*data;
	pthread_t		thread;
}	t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				eat_count;
	int				ate;
	int				dead;
	int				all_eat;
	int				mutex_lock;
	struct timeval	start;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing;
	pthread_mutex_t	lock;
}	t_data;

//Init
void		init_philos(t_data *data);
int			init_mutex(t_data *data);
int			data_init(int argc, char **args, t_data *data);
int			check_args(t_data *data, char **args, int argc);
int			one_philo(t_data *data);

//Philo
int			philo_creator(t_data *data);
void		*philo_routine(void *vargp);
int			philo_check_death(t_data *data, t_philo *philo);
void		philo_check_exit(t_data *data, t_philo *philos);
int			simulation_stop(t_philo *philo);

//Actions
int			philo_eat(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			philo_think(t_philo *philo);

//Utils
long int	timestamp(t_philo *philo);
void		ft_usleep(t_philo *philo, useconds_t time);
void		philo_display(t_philo *philo, char *str);
int			ft_atoi(const char *str);
void		*ft_calloc(int count, int size);

#endif
