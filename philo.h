/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 10:24:42 by brettlecler       #+#    #+#             */
/*   Updated: 2023/08/18 12:37:47 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h> //the name says it all
# include <sys/time.h> //gettimeofday
# include <stdio.h> //perrors & printf
# include <stdlib.h> //malloc
# include <string.h> //memset
# include <unistd.h> //usleep
# include <stdbool.h> //boolean variables

typedef struct s_philo
{
	int				id;
	int				eat_count;
	bool			full;
	u_int64_t		time_to_die;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	lock;
	struct s_struct	*data;
}	t_philo;

typedef struct s_struct
{
	int				nb_philo;
	int				nb_meals;
	bool			dead;
	int				complete;
	uint64_t		start_time;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	pthread_t		*th;
	pthread_t		th_mon;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing_lock;
	pthread_mutex_t	data_lock;
	t_philo			*philos;
}	t_struct;

int64_t		ft_atoi(const char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_parsing(int argc, char **argv, t_struct *args);
int			ft_isnotnum(char *str);
int			ft_initialise(int argc, char **argv, t_struct *args);
int			ft_alloc(t_struct *args);
void		ft_allocate_forks_philos(t_struct *args);
u_int64_t	ft_get_time(void);
int			ft_pthread(t_struct *args);
void		ft_eat_sleep(t_philo *philo);
void		ft_message(char *str, t_philo *philo);
void		*ft_th_philo(void *philo_pointer);
void		*ft_th_mon(void *philo_pointer);
int			ft_error(t_struct *args, int num);
void		ft_free_and_destroy(t_struct *args);
int			ft_usleep(useconds_t time);
int			ft_checker(t_struct *args);

#endif