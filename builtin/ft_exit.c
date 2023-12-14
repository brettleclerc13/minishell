/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:26:36 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/09 14:59:28 by brettlecler      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static long int	ft_atol(char *str)
{
	int			i;
	int			minus;
	long int	result;

	i = 0;
	minus = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		minus *= -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] && (str[i] >= 48 && str[i] <= 57))
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	return (minus * result);
}

static bool	ft_isvalidarg(char *arg)
{
	int		i;
	bool	positive;

	positive = true;
	i = 0;
	if (arg[i] == '-')
	{
		positive = false;
		i++;
	}
	else if (arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i++]))
			return (false);
	}
	if (ft_strlen(arg) == 19)
	{
		if ((positive && arg[i - 1] > '7') || (!positive && arg[i - 1] > 8))
			return (false);
	}
	else if (ft_strlen(arg) > 19)
		return (false);
	return (true);
}

static void	ft_put_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(2);
}

void	ft_exit(char **args, pid_t child)
{
	if (child != 0)
		printf("exit\n");
	if (ft_arraylen(args) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit(1);
	}
	else if (ft_arraylen(args) == 2)
	{
		if (!ft_isvalidarg(args[1]))
			ft_put_exit_error(args[1]);
		exit(ft_atol(args[1]) % 256);
	}
	else
	{
		exit (0);
	}
}
