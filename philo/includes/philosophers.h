/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:35:24 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 16:28:29 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_table;

typedef struct s_philo
{
	unsigned long long			last_meat;
	int							fork_left;
	int							fork_right;
	int							index;
	int							number_meat;
	int							alive;
	pthread_mutex_t				n_meat;
	struct s_table				*table;
}				t_philo;

typedef struct s_table
{
	pthread_mutex_t				*forks;
	pthread_mutex_t				write_message;
	pthread_mutex_t				death_check;
	pthread_mutex_t				time_eat;
	pthread_t					*thread;
	pthread_t					death;
	pthread_t					all_eat;
	t_philo						*philo;
	int							total_philo;
	int							max_meat;
	int							is_all_philo_alive;
	unsigned long long			start;
	unsigned long long			time_to_die;
	unsigned long long			time_to_eat;
	unsigned long long			time_to_sleep;
}				t_table;

int					ft_strlen(char *s);
int					test_str(char *str);
int					loop_check_eat(t_table *t);
int					check_arg(int argc, char **argv);
int					incremeant_i(int i, int total_philo);
int					philosophers(t_table *table, t_philo *philo);

long int			ft_atol(const char *str);

unsigned long long	get_time(void);

void				wait_time(unsigned long long time, t_philo *philo);
void				free_all(t_table *table);
void				destroy_mutex(t_table *table);
void				loop_death(t_table *table, int i);

void				*death_check(void *arg);
void				*thread_philo(void *arg);
void				*all_eat_check(void *arg);

void				eat_philo(t_philo *philo);
void				all_thinking(t_table *table);
void				join_all_thread(t_table *table);
void				print_action(t_philo *philo, char *str, char *color);

t_philo				get_info_philo(t_table *table, int i);
t_philo				*initalize_philo(t_table *table, int total_philo);

t_table				*initialize_all(char **argv);
t_table				*initialize_table(char **argv);

pthread_t			*initalize_thread(int n_philo);

pthread_mutex_t		*init_mutex(int total_philo);

#endif
