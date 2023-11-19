/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everonel <everonel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:58:47 by everonel          #+#    #+#             */
/*   Updated: 2023/07/16 01:22:18 by everonel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int ac, char **av)
{
	t_table	*table;
	int		i;

	i = 0;
	if (!ft_bouncer(ac, av))
		return (printf("Usage: number_of_philosophers time_to_die time_to_eat"
				"time_to_sleep [number_of_times_each_philosopher_must_eat]\n")
			, 1);
	table = ft_lay_table(ac, av);
	table->philos = ft_introduce_guests(table, av);
	ft_seat_guests(table);
	ft_farewell_guests(table);
	return (0);
}

void	ft_seat_guests(t_table *table)
{
	struct timeval	time;
	int				i;
	int				dead;

	i = 0;
	gettimeofday(&time, NULL);
	table->start_time = ft_time_to_ms(time);
	while (i < table->philo_num)
	{
		table->philos[i].start_time = table->start_time;
		pthread_create(&table->philos[i].thread, NULL, &ft_dinner_routine,
			&table->philos[i]);
		usleep(200);
		i++;
	}
	pthread_create(&table->waiter, NULL, &ft_waiter_routine, (void *)table);
	ft_check_dishes(table, &dead);
	while (i--)
		pthread_join(table->philos[i].thread, NULL);
	pthread_join(table->waiter, NULL);
}

void	ft_farewell_guests(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->mutx_forks[i]);
		i++;
	}
	free(table->mutx_forks);
	free(table->philos);
	pthread_mutex_destroy(&table->mutx_eat);
	pthread_mutex_destroy(&table->mutx_write);
	pthread_mutex_destroy(&table->mutx_death);
	pthread_mutex_destroy(&table->mutx_clock);
	free(table);
}
