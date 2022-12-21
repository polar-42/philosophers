/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg  <fle-tolg@student.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:53:34 by fle-tolg          #+#    #+#             */
/*   Updated: 2022/12/21 14:52:54 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_action(t_philo *philo, char *str, char *color)
{
	pthread_mutex_lock(&philo->table->death_check);
	pthread_mutex_lock(&philo->table->time_eat);
	if (philo->table->is_all_philo_alive == 1)
	{
		pthread_mutex_lock(&philo->table->write_message);
		printf("%s%llu %i %s\n\033[0m", color, (get_time() - \
			philo->table->start), philo->index + 1, str);
		pthread_mutex_unlock(&philo->table->write_message);
	}
	pthread_mutex_unlock(&philo->table->death_check);
	pthread_mutex_unlock(&philo->table->time_eat);
}

void	all_thinking(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->total_philo)
	{
		print_action(&table->philo[i], "is thinking", "\033[0;36m");
		i++;
	}
}
