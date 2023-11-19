/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_dinner_room.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everonel <everonel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:36:42 by everonel          #+#    #+#             */
/*   Updated: 2023/07/16 02:07:54 by everonel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_bouncer(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (0);
	while (++i < ac)
	{
		if (!ft_isint(av[i]))
			return (printf("Error\n"), 0);
	}
	while (i-- >= 1)
	{
		if (ft_atoi(av[i]) < 0)
			return (printf("Error\n"), 0);
	}
	if (ft_atoi(av[1]) == 0)
		return (printf("No guests no dinner\n"), 0);
	return (1);
}

t_table	*ft_lay_table(int ac, char **av)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)malloc(sizeof(t_table));
	table->philos = NULL;
	table->philo_num = ft_atoi(av[1]);
	table->dead = 0;
	table->die_time = ft_atoi(av[2]) * 1000;
	table->eat_count = 0;
	if (ac == 6)
		table->dishes = ft_atoi(av[5]);
	else
		table->dishes = -1;
	pthread_mutex_init(&table->mutx_eatc, NULL);
	pthread_mutex_init(&table->mutx_eat, NULL);
	pthread_mutex_init(&table->mutx_write, NULL);
	pthread_mutex_init(&table->mutx_clock, NULL);
	pthread_mutex_init(&table->mutx_death, NULL);
	table->mutx_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* table->philo_num);
	while (i++ < table->philo_num)
		if (pthread_mutex_init(&table->mutx_forks[i - 1], NULL) != 0)
			break ;
	return (table);
}

t_philo	*ft_introduce_guests(t_table *table, char **av)
{
	int	i;

	i = 0;
	table->philos = (t_philo *)malloc(sizeof(t_philo) * table->philo_num);
	while (i < table->philo_num)
	{
		table->philos[i].id = i + 1;
		ft_assign_forks(table, i);
		table->philos[i].last_eat = 0;
		table->philos[i].philo_num = table->philo_num;
		table->philos[i].die_time = table->die_time;
		table->philos[i].eat_time = ft_atoi(av[3]) * 1000;
		table->philos[i].sleep_time = ft_atoi(av[4]) * 1000;
		table->philos[i].start_time = table->start_time;
		table->philos[i].dead = &table->dead;
		table->philos[i].eat_count = &table->eat_count;
		table->philos[i].mutx_eatc = &table->mutx_eatc;
		table->philos[i].mutx_eat = &table->mutx_eat;
		table->philos[i].mutx_clock = &table->mutx_clock;
		table->philos[i].mutx_write = &table->mutx_write;
		table->philos[i].mutx_death = &table->mutx_death;
		i++;
	}
	return (table->philos);
}

void	ft_assign_forks(t_table *table, int pos)
{
	if (table->philo_num == 1)
	{
		table->philos[pos].mutx_lfork = &table->mutx_forks[pos];
		return ;
	}
	if (pos == 0)
	{
		table->philos[pos].mutx_lfork = &table->mutx_forks[pos];
		table->philos[pos].mutx_rfork = &table->mutx_forks[pos + 1];
	}
	if (pos > 0 && pos < table->philo_num -1)
	{
		table->philos[pos].mutx_lfork = &table->mutx_forks[pos];
		table->philos[pos].mutx_rfork = &table->mutx_forks[pos + 1];
	}
	if (pos == table->philo_num - 1)
	{
		table->philos[pos].mutx_lfork = &table->mutx_forks[0];
		table->philos[pos].mutx_rfork = &table->mutx_forks[pos];
	}
}
