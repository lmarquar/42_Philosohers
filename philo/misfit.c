/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misfit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:20:43 by leon              #+#    #+#             */
/*   Updated: 2022/05/03 12:23:59 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	terminate_all(t_phil *p)
{
	t_phil	*tmp;

	p = p->first;
	tmp = p;
	while (tmp)
	{
		pthread_mutex_destroy(p->fork_left);
		free(p->fork_left);
		tmp = tmp->next;
		if (tmp == NULL)
		{
			pthread_mutex_unlock(p->m_printf);
			pthread_mutex_destroy(p->m_printf);
			pthread_mutex_unlock(p->m_dead);
			pthread_mutex_destroy(p->m_dead);
			free(p->m_printf);
			free(p->m_dead);
		}
		free(p);
		p = tmp;
	}
	return (0);
}

int	p_set_dead(t_phil *p)
{
	pthread_mutex_lock(p->m_dead);
	p->dead = 1;
	pthread_mutex_unlock(p->m_dead);
	return (0);
}

int	check_if_dead(t_phil *p)
{
	int		x;
	t_phil	*t;

	x = 0;
	pthread_mutex_lock(p->m_dead);
	t = p->first;
	while (t)
	{
		if (t->dead)
			x++;
		t = t->next;
	}
	pthread_mutex_unlock(p->m_dead);
	return (x);
}

int	m_printf_func(t_phil *p, int i)
{
	int		x;

	pthread_mutex_lock(p->m_printf);
	x = check_if_dead(p);
	if ((x && i != 4) || x > 1)
	{
		pthread_mutex_unlock(p->m_printf);
		return (1);
	}
	if (i == 0)
		printf("%ld %d has taken a fork\n", time_ms(), p->id);
	else if (i == 1)
		printf("%ld %d is eating\n", time_ms(), p->id);
	else if (i == 2)
		printf("%ld %d is sleeping\n", time_ms(), p->id);
	else if (i == 3)
		printf("%ld %d is thinking\n", time_ms(), p->id);
	else if (i == 4)
	{
		printf("%ld %d died\n", time_ms(), p->id);
		pthread_mutex_unlock(p->m_printf);
		return (1);
	}
	pthread_mutex_unlock(p->m_printf);
	return (0);
}
