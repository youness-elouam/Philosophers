/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 12:54:29 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/08/09 14:15:15 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	init_mutexs(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
	if (!table->forks)
		return (1);
	while (i < table->num_philos)
	{
		if (pthread_mutex_init(&table->forks[i++], NULL))
		{
			free(table->forks);
			return (1);
		}
	}
	if (pthread_mutex_init(&table->print, NULL))
		return (1);
	if (pthread_mutex_init(&table->first, NULL))
		return (1);
	if (pthread_mutex_init(&table->died, NULL))
		return (1);
	return (0);
}

int	check_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi(av[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

int	philo_init(int ac, char **av, t_table *table)
{
	if (check_args(av))
		return (1);
	table->num_philos = ft_atoi(av[1]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->is_died = 0;
	table->is_first = 1;
	if (ac == 6)
	{
		table->n_philo_eat = ft_atoi(av[5]);
		table->is_have_eatnum = 1;
	}
	else
		table->is_have_eatnum = 0;
	if (init_mutexs(table))
		return (1);
	return (0);
}

void	print_action(int id, char *action, t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	if (philo->table->is_died == 0)
		printf("%ld %d %s\n", init_time(GET), id, action);
	pthread_mutex_unlock(&philo->table->print);
}

void	set_philos(int i, t_table *table, t_philo *philo)
{
	philo->philo_id = (i + 1);
	philo->table = table;
	philo->r_fork = &table->forks[i];
	philo->num_of_eat = 0;
	if (i == 0)
		philo->l_fork = &table->forks[table->num_philos - 1];
	else
		philo->l_fork = &table->forks[i - 1];
}
