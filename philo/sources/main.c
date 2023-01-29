/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:32:50 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/10 10:21:20 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void eat_philo_2(t_philo *philo)
{
	if (philo->table->time_to_die < philo->table->time_to_eat)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->fork_right]);
		pthread_mutex_unlock(&philo->table->forks[philo->fork_left]);
		usleep((philo->table->time_to_die + 100) * 1000);
		return;
	}
	else
		wait_time(philo->table->time_to_eat * 1000, philo);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_right]);
	pthread_mutex_unlock(&philo->table->forks[philo->fork_left]);
	pthread_mutex_lock(&philo->n_meat);
	philo->number_meat++;
	pthread_mutex_unlock(&philo->n_meat);
	print_action(philo, "is sleeping", "\033[0;32m");
	wait_time(philo->table->time_to_sleep * 1000, philo);
	print_action(philo, "is thinking", "\033[0;36m");
}

void eat_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks[philo->fork_right]);
	print_action(philo, "has taken a fork", "\033[0;34m");
	if (philo->table->total_philo == 1)
	{
		pthread_mutex_unlock(&philo->table->forks[philo->fork_right]);
		usleep(philo->table->time_to_die * 1000);
		return;
	}
	pthread_mutex_lock(&philo->table->forks[philo->fork_left]);
	print_action(philo, "has taken a fork", "\033[0;34m");
	print_action(philo, "is eating", "\033[0;33m");
	pthread_mutex_lock(&philo->table->time_eat);
	philo->last_meat = get_time();
	pthread_mutex_unlock(&philo->table->time_eat);
	eat_philo_2(philo);
}

void *thread_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 != 0)
		usleep(15000);
	pthread_mutex_lock(&philo->table->death_check);
	while (philo->table->is_all_philo_alive == 1)
	{
		pthread_mutex_unlock(&philo->table->death_check);
		eat_philo(philo);
		pthread_mutex_lock(&philo->table->death_check);
	}
	pthread_mutex_unlock(&philo->table->death_check);
	return (0);
}

int philosophers(t_table *table, t_philo *philo)
{
	int i;
	int tmp;

	all_thinking(table);
	i = pthread_create(&table->death, NULL, death_check, table);
	if (i != 0)
		return (1);
	if (table->max_meat != -1)
		pthread_create(&table->all_eat, NULL, all_eat_check, table);
	if (i != 0)
		return (1);
	i = 0;
	while (i < table->total_philo)
	{
		tmp = pthread_create(&table->thread[i], NULL, thread_philo, &philo[i]);
		if (tmp != 0)
			return (1);
		i++;
	}
	join_all_thread(table);
	return (0);
}

int main(int argc, char **argv)
{
	t_table *table;
	t_philo *philo;

	if (check_arg(argc, argv) == 0)
	{
		write(2, "Error\nNo-valid argument\n", 25);
		return (1);
	}
	table = initialize_all(argv);
	if (!table)
		return (1);
	philo = table->philo;
	table->thread = initalize_thread(ft_atol(argv[1]));
	if (!table->thread)
		return (1);
	table->forks = init_mutex(table->total_philo);
	philosophers(table, philo);
	destroy_mutex(table);
	free_all(table);
	return (0);
}
