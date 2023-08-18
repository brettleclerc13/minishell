/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:23:30 by brettlecler       #+#    #+#             */
/*   Updated: 2023/08/18 12:15:23 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_error(NULL, 4);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

int	ft_usleep(useconds_t time)
{
	u_int64_t	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	ft_checker(t_struct *args)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&args->philos[i].lock);
		if (ft_get_time() >= args->philos[i].time_to_die)
		{
			ft_message("died", &args->philos[i]);
			return (1);
		}
		if (args->philos[i].eat_count >= args->nb_meals
			&& args->philos[i].full == false)
		{
			pthread_mutex_lock(&args->data_lock);
			args->complete++;
			args->philos[i].full = true;
			pthread_mutex_unlock(&args->data_lock);
		}
		pthread_mutex_unlock(&args->philos[i].lock);
		i++;
		if (i == args->nb_philo)
			i = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	t_struct	args;

	i = -1;
	if (ft_parsing(argc, argv, &args) == 1)
		return (1);
	if (ft_pthread(&args))
		return (1);
	if (ft_checker(&args))
	{
		i = -1;
		while (++i < args.nb_philo)
			if (pthread_detach(args.th[i]))
				return (ft_error(&args, 10));
	}
	else
	{
		i = -1;
		while (++i < args.nb_philo)
			if (pthread_join(args.th[i], NULL))
				return (ft_error(&args, 8));
	}
	ft_free_and_destroy(&args);
	return (0);
}

// system("leaks philo");