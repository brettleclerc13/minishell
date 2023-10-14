/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:51:58 by ehouot            #+#    #+#             */
/*   Updated: 2023/06/13 15:27:28 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2, bool free_first_param);
char	*ft_strdup_gnl(const char *s1);
char	*ft_strcpy_gnl(char *dst, const char *src);
char	*ft_strchr_gnl(const char *s, int c);
size_t	ft_strlen_gnl(const char *s);

#endif