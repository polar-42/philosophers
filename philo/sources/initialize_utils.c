/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:37:41 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/07 14:26:36 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

t_philo	get_info_philo(t_table *table, int i)
{
	t_philo	philo;

	philo.index = i;
	philo.fork_right = i;
	philo.fork_left = i - 1;
	if ((i - 1) < 0)
		philo.fork_left = table->total_philo - 1;
	if (table->total_philo == 1)
		philo.fork_left = -1;
	philo.number_meat = 0;
	pthread_mutex_init(&philo.n_meat, NULL);
	philo.last_meat = get_time();
	philo.alive = 1;
	return (philo);
}

t_philo	*initalize_philo(t_table *table, int total_philo)
{
	int			i;
	t_philo		*philo;

	philo = malloc((total_philo) * sizeof(t_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < total_philo)
	{
		philo[i] = get_info_philo(table, i);
		philo[i].table = table;
		i++;
	}
	return (philo);
}

t_table	*initialize_table(char **argv)
{
	t_table		*table;

	table = malloc(1 * sizeof(t_table));
	if (!table)
		return (NULL);
	table->total_philo = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	table->is_all_philo_alive = 1;
	table->max_meat = -1;
	if (argv[5])
		table->max_meat = ft_atol(argv[5]);
	table->start = get_time();
	if (table->start == 1)
		return (NULL);
	return (table);
}

t_table	*initialize_all(char **argv)
{
	t_table	*table;

	table = initialize_table(argv);
	if (!table)
		return (NULL);
	table->philo = initalize_philo(table, table->total_philo);
	if (!table->philo)
		return (NULL);
	pthread_mutex_init(&table->write_message, NULL);
	pthread_mutex_init(&table->death_check, NULL);
	pthread_mutex_init(&table->time_eat, NULL);
	return (table);
}
