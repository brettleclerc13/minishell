/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brettleclerc <brettleclerc@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 20:01:37 by brettlecler       #+#    #+#             */
/*   Updated: 2023/11/29 14:40:21 by brettlecler      ###   ########.fr       */
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
		if (!ft_strncmp(array[i], removeline, ft_strlen(removeline)))
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
	tmp = ft_calloc(ft_arraylen(array) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (array[++i] && array)
		tmp[i] = ft_strdup(array[i]);
	return (tmp);
}
