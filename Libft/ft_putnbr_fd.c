/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:51:52 by ehouot            #+#    #+#             */
/*   Updated: 2023/11/16 08:25:49 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print(int n, int i, char *mod, int fd)
{
	if (n == -2147483648)
		write (fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write (fd, "-", 1);
			n *= -1;
		}
		while ((n / 10) > 0)
		{
			i++;
			mod[i] = (n % 10) + 48;
			n = n / 10;
		}
		mod[i + 1] = n + 48;
		while (i + 1 > 0)
		{
			write (fd, &mod[i + 1], 1);
			i--;
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int		i;
	char	mod[13];

	i = 0;
	ft_print(n, i, mod, fd);
}
