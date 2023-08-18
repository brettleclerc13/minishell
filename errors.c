/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 12:14:54 by brettlecler       #+#    #+#             */
/*   Updated: 2023/08/18 12:11:29 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(t_struct *args, int num)
{
	if (num == 1)
		printf("Wrong number of arguments\n");
	if (num == 2)
		printf("Arguments should contain only digits\n");
	if (num == 3)
		printf("Only positive integers accepted\n");
	if (num == 4)
		perror("Gettimeofday function issue\n");
	if (num == 5)
		printf("At least one philosopher needed\n");
	if (num == 6)
		perror("Malloc issue\n");
	if (num == 7)
		perror("Pthread create function issue\n");
	if (num == 8)
		perror("Pthread join function issue\n");
	if (num == 9)
		perror("Number of meals should at least be 1\n");
	if (num == 10)
		perror("Pthread detach function issue\n");
	if (args)
		ft_free_and_destroy(args);
	return (1);
}

void	ft_free_and_destroy(t_struct *args)
{
	int	i;

	i = -1;
	if (args)
	{
		while (++i < args->nb_philo)
		{
			pthread_mutex_destroy(&args->forks[i]);
			pthread_mutex_destroy(&args->philos[i].lock);
		}
		pthread_mutex_destroy(&args->writing_lock);
		pthread_mutex_destroy(&args->data_lock);
	}
	if (args->th)
		free(args->th);
	if (args->forks)
		free(args->forks);
	if (args->philos)
		free(args->philos);
}
