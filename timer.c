/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:59:51 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/08/05 13:42:55 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	m_sleep(int t)
{
	struct	timeval tv;	
	int		time;

	gettimeofday(&tv, NULL);
	time = tv.tv_usec;
	while(tv.tv_usec - time  <= t)
		gettimeofday(&tv, NULL);	
}

int	init_time(t_method method)
{
	static struct timeval	tv;
	struct timeval			time;

	if (method == SET)
	{
		gettimeofday(&tv, NULL);
		return (tv.tv_usec);
	}
	gettimeofday(&time, NULL);
	return(time.tv_usec - tv.tv_usec);
}

long int	check_life(t_method method)
{
	static struct timeval	last_eat;
	struct timeval			time;

	if (method == SET)
	{
		gettimeofday(&last_eat, NULL);
		return (last_eat.tv_usec);
	}
	gettimeofday(&time, NULL);
	return(time.tv_usec - last_eat.tv_usec);
}