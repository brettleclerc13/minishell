/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 21:04:45 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/13 15:25:15 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*catch_before_nl(char *line)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc (BUFFER_SIZE + 1);
	if (!res)
		return (NULL);
	while (line[i] != '\n')
	{
		res[i] = line[i];
		i++;
	}
	res[i] = '\n';
	res[i + 1] = '\0';
	return (res);
}

static char	*check_nl_stash(char *stash, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strchr_gnl(stash, '\n');
	if (tmp == NULL)
	{
		line = ft_strdup_gnl(stash);
		while (stash[i] != '\n' && stash[i])
		{
			stash[i] = '\0';
			i++;
		}
	}
	else
	{
		line = catch_before_nl(stash);
		stash = ft_strcpy_gnl(stash, (tmp + 1));
	}
	return (line);
}

static char	*read_line(int fd, char *line)
{
	int		i;
	int		j;
	char	buffer[BUFFER_SIZE + 1];

	i = 1;
	j = -1;
	while (++j < BUFFER_SIZE)
		buffer[j] = '\0';
	while (ft_strchr_gnl(buffer, '\n') == NULL && i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(line);
			return (NULL);
		}
		if (i == 0)
			return (line);
		buffer[i] = '\0';
		if (line == NULL)
			line = ft_strdup_gnl(buffer);
		else
			line = ft_strjoin_gnl(line, buffer, true);
	}
	return (line);
}

static char	*cut_line(char *line, char *stash)
{
	int	i;
	int	j;
	int	save;

	i = 0;
	j = 0;
	save = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (line);
	save = i;
	i++;
	while (line[i])
	{
		stash[j] = line[i];
		i++;
		j++;
	}
	line[save + 1] = '\0';
	stash[j] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	size_t		i;

	i = 0;
	line = NULL;
	if (!stash[0])
		stash[0] = '\0';
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (stash[i])
	{
		line = check_nl_stash(stash, line);
		while (line[i] != '\n' && line[i])
			i++;
		if (i != ft_strlen_gnl(line))
			return (line);
	}
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	line = cut_line(line, stash);
	return (line);
}
