/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg  <fle-tolg@student.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 15:53:00 by fle-tolg          #+#    #+#             */
/*   Updated: 2022/12/21 15:12:10 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

pthread_t	*initalize_thread(int n_philo)
{
	pthread_t	*thread;

	thread = malloc((n_philo) * sizeof(pthread_t));
	if (!thread)
		return (NULL);
	return (thread);
}

void	join_all_thread(t_table *table)
{
	int	i;

	i = 0;
	pthread_join(table->death, NULL);
	pthread_join(table->all_eat, NULL);
	while (i < table->total_philo)
	{
		pthread_join(table->thread[i], NULL);
		i++;
	}
}

int	loop_check_eat(t_table *t)
{
	int		i;

	i = 0;
	pthread_mutex_lock(&t->philo[i].n_meat);
	while (t->philo[i].number_meat >= t->max_meat \
			&& i < t->total_philo)
	{
		pthread_mutex_unlock(&t->philo[i].n_meat);
		i++;
		if (i >= t->total_philo)
		{
			pthread_mutex_lock(&t->death_check);
			t->is_all_philo_alive = 0;
			pthread_mutex_unlock(&t->death_check);
			return (1);
		}
		pthread_mutex_lock(&t->philo[i].n_meat);
	}
	pthread_mutex_unlock(&t->philo[i].n_meat);
	return (0);
}

void	*all_eat_check(void *arg)
{
	t_table		*t;

	t = (t_table *)arg;
	pthread_mutex_lock(&t->death_check);
	while (t->is_all_philo_alive == 1)
	{
		pthread_mutex_unlock(&t->death_check);
		usleep(10000);
		if (loop_check_eat(t) == 1)
			return (0);
		pthread_mutex_lock(&t->death_check);
	}
	pthread_mutex_unlock(&t->death_check);
	return (0);
}

void	loop_death(t_table *table, int i)
{
	pthread_mutex_unlock(&table->time_eat);
	pthread_mutex_lock(&table->death_check);
	table->is_all_philo_alive = 0;
	pthread_mutex_unlock(&table->death_check);
	pthread_mutex_lock(&table->write_message);
	printf("\033[0;31m%llu %i is died\n\033[0m", \
		(get_time() - table->start), table->philo[i].index + 1);
	pthread_mutex_unlock(&table->write_message);
}
