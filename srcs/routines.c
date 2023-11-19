/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everonel <everonel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:37:36 by everonel          #+#    #+#             */
/*   Updated: 2023/07/16 01:20:20 by everonel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*ft_waiter_routine(void *args)
{
	t_table	*table;
	int		i;
	int		last_eat;
	int		dishes;

	table = (t_table *)args;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->mutx_eatc);
		last_eat = table->philos[i].last_eat;
		pthread_mutex_unlock(&table->mutx_eatc);
		pthread_mutex_lock(&table->mutx_eat);
		dishes = table->dishes;
		pthread_mutex_unlock(&table->mutx_eat);
		if (ft_check_death(table, table->philos[i], dishes, last_eat) == 0)
			break ;
		i++;
		if (i == table->philo_num)
			i = 0;
		usleep(10);
	}
	return (NULL);
}

void	*ft_dinner_routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	pthread_mutex_lock(philo->mutx_eatc);
	philo->last_eat = 0;
	pthread_mutex_unlock(philo->mutx_eatc);
	while (1)
	{
		pthread_mutex_lock(philo->mutx_death);
		if (*philo->dead)
			return (pthread_mutex_unlock(philo->mutx_death), NULL);
		pthread_mutex_unlock(philo->mutx_death);
		if (!ft_take_forks(philo))
			return (NULL);
		ft_eat(philo);
		ft_broadcasting(philo, "is sleeping", 0);
		usleep(philo->sleep_time);
		ft_broadcasting(philo, "is thinking", 0);
		usleep(10);
	}
	return (NULL);
}

int	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->mutx_lfork);
	ft_broadcasting(philo, "has taken a fork", 0);
	if (philo->philo_num == 1)
	{
		usleep(philo->die_time);
		return (pthread_mutex_unlock(philo->mutx_lfork), 0);
	}
	pthread_mutex_lock(philo->mutx_rfork);
	ft_broadcasting(philo, "has taken a fork", 0);
	return (1);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->mutx_eatc);
	philo->last_eat = ft_current_time(philo) * 1000;
	pthread_mutex_unlock(philo->mutx_eatc);
	ft_broadcasting(philo, "is eating", 0);
	usleep(philo->eat_time);
	pthread_mutex_lock(philo->mutx_eat);
	*philo->eat_count += 1;
	pthread_mutex_unlock(philo->mutx_eat);
	pthread_mutex_unlock(philo->mutx_lfork);
	pthread_mutex_unlock(philo->mutx_rfork);
}
