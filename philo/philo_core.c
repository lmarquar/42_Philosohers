/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:08:12 by leon              #+#    #+#             */
/*   Updated: 2022/05/03 12:10:30 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_eat2(t_phil *p)
{
	if (check_if_dead(p))
	{
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		return (1);
	}
	m_printf_func(p, 0);
	gettimeofday(&(p->end_time), NULL);
	if (time_diff(&(p->start_time), &(p->end_time)) > p->death)
	{
		p_set_dead(p);
		m_printf_func(p, 4);
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		return (1);
	}
	m_printf_func(p, 1);
	if (time_loop(p->end_time, p->eat, p))
	{
		pthread_mutex_unlock(p->fork_left);
		pthread_mutex_unlock(p->fork_right);
		return (1);
	}
	return (0);
}

int	phil_eat(t_phil *p)
{
	pthread_mutex_lock(p->fork_left);
	if (p->n_of_p == 1)
	{
		pthread_mutex_unlock(p->fork_left);
		p_set_dead(p);
		return (m_printf_func(p, 4));
	}
	if (check_if_dead(p))
	{
		pthread_mutex_unlock(p->fork_left);
		return (1);
	}
	m_printf_func(p, 0);
	pthread_mutex_lock(p->fork_right);
	if (phil_eat2(p))
		return (1);
	pthread_mutex_unlock(p->fork_left);
	pthread_mutex_unlock(p->fork_right);
	p->just_slept = 0;
	m_printf_func(p, 2);
	p->start_time = p->end_time;
	p->i_loop = p->i_loop + 1;
	return (0);
}

int	life_loop(t_phil *p)
{
	while (p->i_loop < p->loops || p->loops == -1)
	{
		if (p->just_slept)
		{
			if (p->id == 0 && (p->n_of_p + 2) % 2)
				usleep(100);
			if (phil_eat(p))
				return (1);
		}
		else
		{
			if (time_loop(p->start_time, p->eat + p->sleep, p))
				return (1);
			m_printf_func(p, 3);
			p->just_slept = 1;
		}
	}
	pthread_mutex_lock(p->m_dead);
	p->done = 1;
	pthread_mutex_unlock(p->m_dead);
	return (0);
}

void	*life(void *p_v)
{
	t_phil	*p;

	p = (t_phil *) p_v;
	gettimeofday(&(p->start_time), NULL);
	if (p->start_val)
	{
		if (phil_eat(p))
			return ((void *) &(p->id));
	}
	else
	{
		m_printf_func(p, 2);
		time_loop(p->start_time, p->sleep, p);
		p->just_slept = 1;
	}
	life_loop(p);
	return ((void *) &(p->id));
}
