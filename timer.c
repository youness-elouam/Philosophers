/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 17:59:51 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/08/07 18:27:28 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	m_sleep(int t)
{
	struct	timeval tv;	
	int		time;
	int		c_time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	c_time = time;
	while(c_time - time  <= t)
	{
		usleep(50);
		gettimeofday(&tv, NULL);
		c_time = ((tv.tv_usec / 1000) + (tv.tv_sec * 1000));
	}
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
	return(((time.tv_usec / 1000) + (time.tv_sec * 1000)) - ((tv.tv_usec / 1000) + (tv.tv_sec * 1000)));
}

long int	check_life(t_method method, int i)
{
	static struct timeval	*last_eat;
	struct timeval			time;
	int						t;

	
	t = 0;
	if (method == SET_F)
	{
		last_eat = malloc(sizeof(struct timeval) * i);
		while(t <= i)
		{
			gettimeofday(&last_eat[t], NULL);
			t++;
		}
		return (0);
	}
	if (method == SET)
	{
		gettimeofday(&last_eat[t], NULL);
		return (0);
	}
	if (method == RESET)
	{
		free(last_eat);
		return (0);
	}
	gettimeofday(&time, NULL);
	return(((time.tv_usec / 1000) + (time.tv_sec * 1000)) - ((last_eat[i].tv_usec / 1000) + (last_eat->tv_sec * 1000)));
}