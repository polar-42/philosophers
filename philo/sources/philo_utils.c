/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:53:34 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/07 11:53:57 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	test_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long int	ft_atol(const char *str)
{
	long int	i;
	long int	y;
	long int	s;

	i = 0;
	s = 0;
	y = 1;
	if (test_str((char *)str) == 0)
		return (-1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == 45)
	{
		y *= -1;
		i++;
	}
	else if (str[i] == 43)
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		s = (s * 10) + (str[i] - '0');
		i++;
	}
	return (s * y);
}

int	check_arg(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (ft_atol(argv[1]) <= 0 || ft_atol(argv[1]) > 2147483647
		|| ft_atol(argv[2]) <= 0 || ft_atol(argv[2]) > 2147483647
		|| ft_atol(argv[3]) <= 0 || ft_atol(argv[3]) > 2147483647
		|| ft_atol(argv[4]) <= 0 || ft_atol(argv[4]) > 2147483647)
		return (0);
	if (ft_strlen(argv[1]) >= 12 || ft_strlen(argv[2]) >= 12
		|| ft_strlen(argv[3]) >= 12 || ft_strlen(argv[4]) >= 12)
		return (0);
	if (argv[5])
		if (ft_atol(argv[5]) <= 0 || ft_atol(argv[5]) > 2147483647)
			return (0);
	return (1);
}

int	ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
