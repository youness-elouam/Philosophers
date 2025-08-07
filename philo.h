/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:03:50 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/08/07 15:47:04 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_table
{
	int				num_philos;
	int				time_to_die;
	int				time_to_sleep;
	int				time_to_eat;
	int				n_philo_eat;
	int				is_have_eatnum;
	int				is_died;
	int				is_first;
	struct s_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t	print;
	pthread_mutex_t	first;
	pthread_mutex_t	died;
}	t_table;

typedef struct s_philo
{
	pthread_t		tid;
	int				philo_id;
	int				last_eat;
	t_table			*table;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *r_fork;
} t_philo;

typedef enum s_method
{
	SET,
	SET_F,
	GET,
	RESET
}	t_method;

int				ft_atoi(const char *str);
int				ft_isdigit(int c);
long int		init_time(t_method method);
void			m_sleep(int t);
void			set_philos(int i, t_table *table, t_philo *philo);
void			print_action(int id, char *action, t_philo *philo);
int				philo_init(int ac, char **av, t_table *table);
int 			init_mutexs(t_table *table);
long int		check_life(t_method method, int i);

#endif