/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:01:37 by brettlecler       #+#    #+#             */
/*   Updated: 2023/12/14 15:44:24 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_arrayremove(char *removeline, char **array)
{
	char	**tmp;
	int		i;
	int		j;

	if (!array)
		return (NULL);
	i = -1;
	j = -1;
	tmp = ft_calloc(ft_arraylen(array), sizeof(char *));
	if (!tmp)
		return (NULL);
	while (array[++i])
	{
		if (!ft_strncmp(removeline, array[i], ft_strlen(array[i]) + 1))
			continue ;
		tmp[++j] = ft_strdup(array[i]);
	}
	ft_arrayfree(array);
	return (tmp);
}

void	ft_arrayfree(char **array)
{
	int	i;

	if (!array)
		return ;
	i = -1;
	if (array[0] == NULL)
	{
		free(array);
		return ;
	}
	else if (!ft_strcmp(array[0], ""))
	{
		free(array[0]);
		free(array);
		return ;
	}
	while (array[++i])
		free(array[i]);
	free(array);
}

char	**ft_arrayadd(char *newline, char **array)
{
	char	**tmp;
	int		i;

	if (!array)
		return (NULL);
	i = -1;
	tmp = ft_calloc(ft_arraylen(array) + 2, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (array[++i])
		tmp[i] = ft_strdup(array[i]);
	tmp[i] = ft_strdup(newline);
	ft_arrayfree(array);
	return (tmp);
}

int	ft_arraylen(char **array)
{
	int	i;

	i = 0;
	while (array[i] && array)
		i++;
	return (i);
}

char	**ft_arraydup(char **array)
{
	char	**tmp;
	int		i;

	i = -1;
	if (!array)
		return (NULL);
	tmp = ft_calloc(ft_arraylen(array) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (array[++i] && array)
		tmp[i] = ft_strdup(array[i]);
	return (tmp);
}
