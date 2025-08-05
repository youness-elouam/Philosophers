/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-ouam <yel-ouam@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:27:47 by yel-ouam          #+#    #+#             */
/*   Updated: 2025/08/05 16:16:05 by yel-ouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int parce_args(char **args)
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
			{
				printf("-------->[%c]->i = %d j = %d\n", args[i][j], i, j);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	action_loop(t_philo *philo)
{
	check_life(SET);
	init_time(SET);
	while(1)
	{
		if (check_life(GET) >= philo->table->time_to_die || philo->table->is_died)
		{
			if (philo->table->is_died == 0)
				print_action(philo->philo_id, "died", &philo->table->print);
			philo->table->is_died = 1;
			exit (0);
		}	
		pthread_mutex_lock(&philo->l_fork);
		print_action(philo->philo_id, "has taken a fork", &philo->table->print);
		pthread_mutex_lock(&philo->r_fork);
		print_action(philo->philo_id, "has taken a fork", &philo->table->print);
		print_action(philo->philo_id, "is eating", &philo->table->print);
		check_life(SET);
		m_sleep(philo->table->time_to_eat);
		pthread_mutex_unlock(&philo->r_fork);
		pthread_mutex_unlock(&philo->l_fork);//lock inversion
		print_action(philo->philo_id, "is sleeping", &philo->table->print);
		m_sleep(philo->table->time_to_sleep);
		print_action(philo->philo_id, "is thinking", &philo->table->print);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *) arg;
	action_loop(&philo);
	return(NULL);
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
		pthread_create(&tid[i], NULL, philo_routine, &philo[i]);
		i += 2;
	}
	i = 1;
	m_sleep(1);
	while (i < table.num_philos)
	{
		set_philos(i, &table, &philo[i]);
		pthread_create(&tid[i], NULL, philo_routine, &philo[i]);
		i += 2;
	}
	i = 0;
	while (i < table.num_philos)
	{
		if (pthread_join(philo[i].tid, NULL) == -1)
			return ;
		i++;
	}
	free(tid);
	free(philo);
}

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5)
		return(printf("this program must take 3 or 4 arguments"), 1);
	write(1, &av[4][3], 1);
	if (parce_args(av))
		return(printf("error : arguments incorrect (must be just digits)"), 10);
	philo_init(ac, av, &table);
	philo_create(table);
}