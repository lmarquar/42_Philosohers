/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 10:36:04 by leon              #+#    #+#             */
/*   Updated: 2022/05/01 13:53:57 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	time_diff(struct timeval *start, struct timeval *end)
{
	long	res;

	res = 1e+6 * (end->tv_sec - start->tv_sec) + end->tv_usec - start->tv_usec;
	return (res);
}

long	time_ms(void)
{
	struct timeval	x;

	gettimeofday(&(x), NULL);
	return (1e+3 * (x.tv_sec) + 1e-3 * x.tv_usec);
}

struct timeval	add_eating_time(struct timeval *current, int eat)
{
	struct timeval	res;

	if ((eat - 1e+6) > 0)
	{
		res.tv_sec = current->tv_sec + 1e-6 * eat;
		eat = eat % 1000000;
	}
	else
		res.tv_sec = current->tv_sec;
	if ((current->tv_usec + eat) > 1e+6)
	{
		res.tv_usec = eat - (1e+6 - current->tv_usec);
		res.tv_sec = res.tv_sec + 1;
	}
	else
		res.tv_usec = current->tv_usec + eat;
	return (res);
}	

int	comp_t(struct timeval *start, struct timeval *end)
{
	if (start->tv_sec < end->tv_sec)
		return (0);
	if (start->tv_sec > end->tv_sec)
		return (1);
	if (start->tv_usec < end->tv_usec)
		return (0);
	if (start->tv_usec >= end->tv_usec)
		return (1);
	return (1);
}

int	time_loop(struct timeval t_cur, int t_to_add, t_phil *p)
{
	struct timeval	t_end;

	t_end = add_eating_time(&t_cur, t_to_add);
	gettimeofday(&(t_cur), NULL);
	while (!comp_t(&t_cur, &t_end))
	{
		if (check_if_dead(p))
			return (1);
		gettimeofday(&(t_cur), NULL);
		usleep(50);
	}
	return (0);
}
