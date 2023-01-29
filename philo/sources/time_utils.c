/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:53:34 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 10:08:47 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

unsigned long long	get_time(void)
{
	int						test;
	unsigned long long		time;
	struct timeval			current_time;

	test = gettimeofday(&current_time, NULL);
	if (test == -1)
		return (1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	wait_time(unsigned long long time, t_philo *philo)
{
	unsigned long long	split_10;
	int					count;

	split_10 = (time / 10);
	count = 0;
	pthread_mutex_lock(&philo->table->death_check);
	while (count < 10 && philo->table->is_all_philo_alive == 1)
	{
		pthread_mutex_unlock(&philo->table->death_check);
		usleep(split_10);
		count++;
		pthread_mutex_lock(&philo->table->death_check);
	}
	pthread_mutex_unlock(&philo->table->death_check);
}
