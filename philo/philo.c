/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 18:40:31 by leon              #+#    #+#             */
/*   Updated: 2022/05/03 11:52:01 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_phil_mutex(t_phil **p, int i)
{
	p[i]->fork_left = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(p[i]->fork_left, NULL);
	if (i == 0)
	{
		p[0]->m_dead = malloc(sizeof(pthread_mutex_t));
		p[0]->m_printf = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(p[0]->m_printf, NULL);
		pthread_mutex_init(p[0]->m_dead, NULL);
		p[0]->fork_right = NULL;
	}
	else
	{
		p[i]->fork_right = p[i - 1]->fork_left;
		p[i]->m_printf = p[0]->m_printf;
		p[i]->m_dead = p[0]->m_dead;
	}	
	return (0);
}

int	init_phil(t_phil **p, int i, int set[])
{
	p[i] = malloc(sizeof(t_phil));
	init_phil_mutex(p, i);
	p[i]->id = i;
	p[i]->n_of_p = set[0];
	p[i]->sleep = 1e+3 * (set[3]);
	p[i]->eat = 1e+3 * (set[2]);
	p[i]->death = 1e+3 * (set[1]);
	p[i]->loops = set[4];
	p[i]->i_loop = 0;
	p[i]->done = 0;
	p[i]->dead = 0;
	p[i]->dead_p = 0;
	p[i]->start_val = 0;
	if ((i + 2) % 2)
		p[i]->start_val = 1;
	if (i > 0)
		p[i - 1]->next = p[i];
	if (i == (set[0] - 1))
		p[0]->fork_right = p[i]->fork_left;
	p[i]->first = p[0];
	p[i]->next = NULL;
	return (0);
}

static
int	dead_or_done2(t_phil	**p, int n_of_p)
{
	int	i;
	int	k;

	i = -1;
	k = 2;
	pthread_mutex_lock((*p)->m_dead);
	while (++i < n_of_p)
	{
		if (p[i]->dead)
		{
			pthread_mutex_unlock((*p)->m_dead);
			i = -1;
			while (++i < n_of_p)
				pthread_join(p[i]->thread, NULL);
			terminate_all(p[0]);
			free(p);
			return (1);
		}
		if (!p[i]->done)
			k = 0;
	}
	pthread_mutex_unlock((*p)->m_dead);
	return (k);
}

int	dead_or_done(t_phil	**p, int n_of_p)
{
	int	k;

	k = 0;
	while (!k)
	{
		usleep(1000);
		k = dead_or_done2(p, n_of_p);
	}
	if (k == 2)
		k = 0;
	return (k);
}

//set: 0=n_of_p 1=deathclock 2=eattime 3=sleeptime (4=loops)
int	main(int argc, char *argv[])
{
	int		set[5];
	int		i;
	t_phil	**p;

	if (take_argv(argv, set, argc))
		return (1);
	i = -1;
	p = malloc(sizeof(t_phil *) * (set[0] + 1));
	while (++i < set[0])
		init_phil(p, i, set);
	i = -1;
	while (++i < set[0])
		pthread_create(&(p[i]->thread), NULL, life, p[i]);
	if (dead_or_done(p, set[0]))
		return (0);
	i = -1;
	while (++i < set[0])
		pthread_join(p[i]->thread, NULL);
	terminate_all(*p);
	free(p);
	return (0);
}
