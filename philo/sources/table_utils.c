/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:19:45 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/07 14:28:36 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	incremeant_i(int i, int total_philo)
{
	if (i == total_philo)
		return (0);
	return (i + 1);
}

void	free_all(t_table *table)
{
	free(table->forks);
	free(table->philo);
	free(table->thread);
	free(table);
}

pthread_mutex_t	*init_mutex(int total_philo)
{
	int					i;
	pthread_mutex_t		*forks;

	forks = malloc((total_philo + 1) * sizeof(pthread_mutex_t));
	if (!forks)
		return (NULL);
	i = 0;
	while (i < total_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

void	destroy_mutex(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->total_philo)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philo[i].n_meat);
		i++;
	}
	pthread_mutex_destroy(&table->time_eat);
	pthread_mutex_destroy(&table->death_check);
	pthread_mutex_destroy(&table->write_message);
}
