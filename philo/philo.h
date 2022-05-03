/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <lmarquar@student.42wolfsburg.de      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 20:16:08 by leon              #+#    #+#             */
/*   Updated: 2022/05/01 17:24:48 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_phil
{
	int				id;
	int				n_of_p;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*m_printf;
	pthread_mutex_t	*m_dead;
	int				start_val;
	struct timeval	start_time;
	struct timeval	end_time;
	pthread_t		thread;
	int				sleep;
	int				just_slept;
	int				eat;
	int				death;
	int				loops;
	int				i_loop;
	int				done;
	int				dead;
	int				dead_p;
	struct s_phil	*first;
	struct s_phil	*next;
}	t_phil;

int				take_argv(char *argv[], int set[], int argc);
void			*life(void *p_v);
long			time_ms(void);
long			time_diff(struct timeval *start, struct timeval *end);
struct timeval	add_eating_time(struct timeval *current, int eat);
int				comp_t(struct timeval *start, struct timeval *end);
int				time_loop(struct timeval t_cur, int t_to_add, t_phil *p);
int				terminate_all(t_phil *p);
int				p_set_dead(t_phil *p);
int				check_if_dead(t_phil *p);
int				m_printf_func(t_phil *p, int i);

#endif
