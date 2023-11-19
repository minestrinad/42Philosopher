/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff_assignment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everonel <everonel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:39:46 by everonel          #+#    #+#             */
/*   Updated: 2023/07/16 01:20:58 by everonel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_check_death(t_table *table, t_philo philo, int dishes, int last_eat)
{
	if (ft_current_time(&philo) * 1000 - last_eat >= table->die_time
		|| dishes == 0)
	{
		pthread_mutex_lock(&table->mutx_death);
		table->dead = 1;
		pthread_mutex_unlock(&table->mutx_death);
		if (dishes != 0)
			ft_broadcasting(&philo, "died", 1);
		return (0);
	}
	return (1);
}

void	ft_check_dishes(t_table *table, int *dead)
{
	int	i;

	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->mutx_eat);
		if (table->dishes == 0)
			return ((void)pthread_mutex_unlock(&table->mutx_eat));
		pthread_mutex_unlock(&table->mutx_eat);
		pthread_mutex_lock(&table->mutx_death);
		*dead = table->dead;
		pthread_mutex_unlock(&table->mutx_death);
		if (*dead)
			break ;
		pthread_mutex_lock(&table->mutx_eat);
		if (table->eat_count == table->philo_num)
		{
			table->dishes -= 1;
			table->eat_count = 0;
		}
		pthread_mutex_unlock(&table->mutx_eat);
		usleep(10);
	}
}

void	ft_broadcasting(t_philo *philo, char *msg, int death_flag)
{
	pthread_mutex_lock(philo->mutx_death);
	if (!*philo->dead || death_flag)
	{
		pthread_mutex_lock(philo->mutx_write);
		printf("%i %i %s\n", ft_current_time(philo), philo->id, msg);
		pthread_mutex_unlock(philo->mutx_write);
	}
	pthread_mutex_unlock(philo->mutx_death);
	return ;
}

int	ft_current_time(t_philo *philo)
{
	int				curr_time;
	struct timeval	time;

	pthread_mutex_lock(philo->mutx_clock);
	gettimeofday(&time, NULL);
	curr_time = ft_time_to_ms(time) - philo->start_time;
	pthread_mutex_unlock(philo->mutx_clock);
	return (curr_time);
}

int	ft_time_to_ms(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
