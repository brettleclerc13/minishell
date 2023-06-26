/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehouot <ehouot@student.42nice.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 10:48:31 by ehouot            #+#    #+#             */
/*   Updated: 2022/12/01 13:30:23 by ehouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_sign(long int tmp, int n)
{
	if (n < 0)
		tmp = n * -1;
	return (tmp);
}

static int	ft_count(long int tmp, int i)
{
	while ((tmp / 10) > 0)
	{
		tmp = tmp / 10;
		i++;
	}
	return (i);
}

static char	*ft_alloc(int neg, char *dest, int i)
{
	if (neg == 0)
	{
		dest = malloc (sizeof(char) * (i + 1));
		if (!dest)
			return (NULL);
		dest[i] = '\0';
	}
	else
	{
		dest = malloc (sizeof(char) * (i + 2));
		if (!dest)
			return (NULL);
		dest[0] = '-';
		dest[i + 1] = '\0';
		i = i + 1;
	}
	return (dest);
}

static char	*ft_implement(int n, char *dest, int i)
{
	if (n < 0)
	{
		n = n * -1;
		i = i + 1;
	}
	while ((n / 10) > 0)
	{
		dest[i - 1] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	dest[i - 1] = n + 48;
	return (dest);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*dest;
	int			neg;
	long int	tmp;

	dest = NULL;
	tmp = n;
	i = 1;
	neg = 0;
	if (n < 0)
		neg = -1;
	if (n <= -2147483648)
		return (ft_strdup("-2147483648"));
	tmp = ft_sign(tmp, n);
	i = ft_count(tmp, i);
	dest = ft_alloc(neg, dest, i);
	if (!dest)
		return (NULL);
	dest = ft_implement(n, dest, i);
	return (dest);
}
