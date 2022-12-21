/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg  <fle-tolg@student.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 13:53:34 by fle-tolg          #+#    #+#             */
/*   Updated: 2022/12/21 14:26:51 by fle-tolg         ###   ########.fr       */
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
