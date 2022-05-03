/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_argv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:14:39 by leon              #+#    #+#             */
/*   Updated: 2022/04/17 20:15:30 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_arg(char *s)
{
	int	i;

	if (*s == '0' && !*(s + 1))
		return (0);
	i = 0;
	if (s[i] < '1' || s[i] > '9')
		return (1);
	while (s[++i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (1);
		if (i > 9)
			return (1);
	}
	return (0);
}

static int	transform(const char *nptr, int si, int x10)
{
	long long	res;
	int			i;

	res = 0;
	i = si;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
		i++;
	i--;
	while (i >= si && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (nptr[i] - '0') * x10 + res;
		x10 = x10 * 10;
		i--;
	}
	if (res > (long long)2147483647 || res < (long long) -2147483648)
		return (0);
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	res;
	int	x10;

	i = 0;
	x10 = 1;
	while (nptr[i] == ' ' || (nptr[i] > 8 && nptr[i] < 14))
		i++;
	if (nptr[i] == '-')
	{
		x10 = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] == '0')
		i++;
	res = transform(nptr, i, x10);
	return (res);
}

int	take_argv(char *argv[], int set[], int argc)
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		write(1, "Error: check your args!\n", 24);
		return (1);
	}
	i = 0;
	while (i < (argc - 1))
	{
		if (check_arg(argv[i + 1]))
		{
			write(1, "Error: check your args!\n", 24);
			return (1);
		}
		set[i] = ft_atoi(argv[i + 1]);
		i++;
	}
	if (argc == 5)
		set[4] = -1;
	return (0);
}
