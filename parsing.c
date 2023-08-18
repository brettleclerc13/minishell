/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:46:55 by brettlecler       #+#    #+#             */
/*   Updated: 2023/08/18 11:58:03 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_allocate_forks_philos(t_struct *args)
{
	int	i;

	i = -1;
	while (++i < args->nb_philo)
	{
		args->philos[i].data = args;
		args->philos[i].id = i + 1;
		args->philos[i].eat_count = 0;
		args->philos[i].full = false;
		args->philos[i].time_to_die = args->time_to_die;
		pthread_mutex_init(&args->philos[i].lock, NULL);
		pthread_mutex_init(&args->forks[i], NULL);
	}
	args->philos[0].left_fork = &args->forks[0];
	args->philos[0].right_fork = &args->forks[args->nb_philo - 1];
	i = 0;
	while (++i < args->nb_philo)
	{
		args->philos[i].left_fork = &args->forks[i];
		args->philos[i].right_fork = &args->forks[i - 1];
	}
}

int	ft_alloc(t_struct *args)
{
	args->th = malloc(sizeof(pthread_t) * args->nb_philo);
	if (!args->th)
		return (ft_error(args, 6));
	args->forks = malloc(sizeof(pthread_mutex_t) * args->nb_philo);
	if (!args->forks)
		return (ft_error(args, 6));
	args->philos = malloc(sizeof(t_philo) * args->nb_philo);
	if (!args->philos)
		return (ft_error(args, 6));
	return (0);
}

int	ft_isnotnum(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45 || str[i] == 43)
		i++;
	while (str[i])
	{
		if (!(str[i] >= 48 && str[i] <= 57))
			return (1);
		i++;
	}
	return (0);
}

int	ft_initialise(int argc, char **argv, t_struct *args)
{
	args->nb_philo = (int)ft_atoi(argv[1]);
	args->time_to_die = (uint64_t)ft_atoi(argv[2]);
	args->time_to_eat = (uint64_t)ft_atoi(argv[3]);
	args->time_to_sleep = (uint64_t)ft_atoi(argv[4]);
	if (argc == 6)
	{
		args->nb_meals = (int)ft_atoi(argv[5]);
		if (args->nb_meals <= 0)
			return (ft_error(NULL, 9));
	}
	else
		args->nb_meals = 0;
	if (args->nb_philo == 0)
		return (ft_error(NULL, 5));
	args->start_time = ft_get_time();
	args->dead = false;
	args->complete = 0;
	pthread_mutex_init(&args->writing_lock, NULL);
	pthread_mutex_init(&args->data_lock, NULL);
	if (ft_alloc(args))
		return (1);
	ft_allocate_forks_philos(args);
	return (0);
}

int	ft_parsing(int argc, char **argv, t_struct *args)
{
	int	i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (ft_error(NULL, 1));
	while (argv[++i])
		if (ft_isnotnum(argv[i]))
			return (ft_error(NULL, 2));
	if (ft_atoi(argv[1]) == -1 || ft_atoi(argv[2]) == -1
		|| ft_atoi(argv[3]) == -1 || ft_atoi(argv[4]) == -1)
		return (ft_error(NULL, 3));
	if (ft_initialise(argc, argv, args))
		return (1);
	return (0);
}
