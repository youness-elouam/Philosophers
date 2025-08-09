/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:27:47 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/08/09 17:56:02 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	parce_args(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	philo_eat_limit(t_philo *philo)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (philo[0].table->is_have_eatnum == 0)
		return (0);
	while (i < philo[0].table->num_philos)
	{
		if (philo[i].num_of_eat >= philo[0].table->n_philo_eat)
			n++;
		i++;
	}
	if (n == philo[0].table->num_philos)
	{
		philo[0].table->is_died = 1;
		return (1);
	}
	return (0);
}

void	check_if_is_die(t_philo *philo)
{
	int		i;
	long	time;

	i = 0;
	time = 0;
	while (philo[i].table->is_died == 0)
	{
		pthread_mutex_lock(&philo->table->died);
		time = init_time(GET) - philo[i].last_eat;
		pthread_mutex_unlock(&philo->table->died);
		if (time >= philo[i].table->time_to_die)
		{
			time = init_time(GET) - philo[i].last_eat;
			print_action(philo[i].philo_id, "died", &philo[i]);
			pthread_mutex_lock(&philo->table->died);
			philo[i].table->is_died = 1;
			pthread_mutex_unlock(&philo->table->died);
			break ;
		}
		if (philo_eat_limit(philo))
			break ;
		if (++i == (philo[0].table->num_philos))
			i = 0;
		usleep(25);
	}
}

void	action_loop(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->table->died);
		if (philo->table->is_died == 1)
		{
			pthread_mutex_unlock(&philo->table->died);
			break ;
		}
		pthread_mutex_unlock(&philo->table->died);
		pthread_mutex_lock(philo->r_fork);
		print_action(philo->philo_id, "has taken a right fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_action(philo->philo_id, "has taken a left fork", philo);
		print_action(philo->philo_id, "is eating", philo);
		philo->num_of_eat++;
		pthread_mutex_lock(&philo->table->died);
		philo->last_eat = init_time(GET);
		pthread_mutex_unlock(&philo->table->died);
		m_sleep(philo->table->time_to_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		print_action(philo->philo_id, "is sleeping", philo);
		m_sleep(philo->table->time_to_sleep);
		print_action(philo->philo_id, "is thinking", philo);
	}
}

void	one_philo(t_philo *philo)
{
	print_action(philo->philo_id, "has taken a right fork", philo);
	m_sleep(philo->table->time_to_die);
	print_action(philo->philo_id, "died", philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	pthread_mutex_lock(&philo->table->first);
	if (philo->table->is_first)
	{
		philo->table->is_first = 0;
		init_time(SET);
	}
	philo->last_eat = init_time(GET);
	pthread_mutex_unlock(&philo->table->first);
	if (philo->table->num_philos == 1)
		one_philo(philo);
	else
		action_loop(philo);
	return (NULL);
}

int	join_threads(int n, pthread_t *tid)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(tid[i], NULL) == -1)
			return (1);
		i++;
	}
	return (0);
}

void	philo_create(t_table table)
{
	int			i;
	pthread_t	*tid;
	t_philo		*philo;

	i = 0;
	philo = malloc(sizeof(t_philo) * table.num_philos);
	tid = malloc(sizeof(pthread_t) * table.num_philos);
	while (i < table.num_philos)
	{
		set_philos(i, &table, &philo[i]);
		pthread_create(&tid[i], NULL, philo_routine, &(philo[i]));
		i += 2;
	}
	i = 1;
	m_sleep(1);
	while (i < table.num_philos)
	{
		set_philos(i, &table, &philo[i]);
		pthread_create(&tid[i], NULL, philo_routine, &(philo[i]));
		i += 2;
	}
	check_if_is_die(philo);
	join_threads(table.num_philos, tid);
	free(tid);
	free(philo);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5)
		return (printf("this program must take 3 or 4 arguments\n"), 1);
	if (parce_args(av))
		return (printf("error: arguments incorrect (must be just digits)\n"), 1);
	if (philo_init(ac, av, &table))
		return (printf("error: arguments incorrect (must be digits >= 0)\n"), 1);
	philo_create(table);
}
