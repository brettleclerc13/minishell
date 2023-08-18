/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 12:25:27 by brettlecler       #+#    #+#             */
/*   Updated: 2023/08/18 11:28:47 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	ft_message("has taken a fork", philo);
	pthread_mutex_lock(philo->left_fork);
	ft_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = ft_get_time() + philo->data->time_to_die;
	ft_message("\x1b[32mis eating\x1b[0m", philo);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	ft_message("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	ft_message(char *str, t_philo *philo)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->data->writing_lock);
	time = ft_get_time() - philo->data->start_time;
	if (ft_strcmp("died", str) == 0 && philo->data->dead == false)
	{
		printf("%llu %d %s\n", time, philo->id, str);
		philo->data->dead = true;
	}
	if (philo->data->dead == false)
		printf("%llu %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->writing_lock);
}

//ft_message("\x1b[32mis eating\x1b[0m", philo);