/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:59:51 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/08/08 17:43:05 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	m_sleep(int t)
{
	struct timeval	tv;	
	int				time;
	int				c_time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	c_time = time;
	while (c_time - time <= t)
	{
		gettimeofday(&tv, NULL);
		c_time = ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
	}
	usleep(25);
}

long int	init_time(t_method method)
{
	static struct timeval	tv;
	struct timeval			time;

	if (method == SET)
	{
		gettimeofday(&tv, NULL);
		return (0);
	}
	gettimeofday(&time, NULL);
	return (((time.tv_usec / 1000) + (time.tv_sec * 1000))
		- ((tv.tv_usec / 1000) + (tv.tv_sec * 1000)));
}
