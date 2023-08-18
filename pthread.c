/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 16:03:46 by brettlecler       #+#    #+#             */
/*   Updated: 2023/08/18 12:03:50 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_th_mon(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	while (philo->data->dead == false)
	{
		pthread_mutex_lock(&philo->data->data_lock);
		if (philo->data->complete >= philo->data->nb_philo)
			philo->data->dead = true;
		pthread_mutex_unlock(&philo->data->data_lock);
	}
	return ((void *)0);
}

void	*ft_th_philo(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	philo->time_to_die = ft_get_time() + philo->data->time_to_die;
	if (philo->data->nb_philo != 1)
		if (philo->id % 2 == 0)
			ft_usleep(philo->data->time_to_eat / 2);
	while (philo->data->dead == false)
	{
		ft_eat_sleep(philo);
		ft_message("is thinking", philo);
	}
	return ((void *)0);
}

int	ft_pthread(t_struct *args)
{
	int	i;

	i = -1;
	args->start_time = ft_get_time();
	if (args->nb_philo == 1)
	{
		if (pthread_create(&args->th[0], NULL, &ft_th_philo, &args->philos[0]))
			return (ft_error(args, 7));
		ft_usleep(20);
		return (0);
	}
	if (args->nb_meals > 0)
	{
		if (pthread_create(&args->th_mon, NULL, &ft_th_mon, &args->philos[0]))
			return (ft_error(args, 7));
	}
	while (++i < args->nb_philo)
	{
		if (pthread_create(&args->th[i], NULL, &ft_th_philo, &args->philos[i]))
			return (ft_error(args, 7));
	}
	ft_usleep(20);
	return (0);
}
