/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: everonel <everonel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 21:04:55 by everonel          #+#    #+#             */
/*   Updated: 2023/07/16 01:20:40 by everonel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*mutx_lfork;
	pthread_mutex_t	*mutx_rfork;
	int				last_eat;
	int				philo_num;
	int				start_time;
	int				eat_time;
	int				sleep_time;
	int				die_time;
	int				*dead;
	int				*eat_count;
	pthread_mutex_t	*mutx_eatc;
	pthread_mutex_t	*mutx_eat;
	pthread_mutex_t	*mutx_clock;
	pthread_mutex_t	*mutx_write;
	pthread_mutex_t	*mutx_death;
}					t_philo;

typedef struct s_table
{
	t_philo			*philos;
	pthread_mutex_t	*mutx_forks;
	pthread_t		waiter;
	int				start_time;
	int				philo_num;
	int				die_time;
	int				dead;
	int				dishes;
	int				eat_count;
	pthread_mutex_t	mutx_eatc;
	pthread_mutex_t	mutx_write;
	pthread_mutex_t	mutx_eat;
	pthread_mutex_t	mutx_death;
	pthread_mutex_t	mutx_clock;
}					t_table;

//      MAIN
int					main(int argc, char **argv);
void				ft_seat_guests(t_table *table);
void				ft_farewell_guests(t_table *table);

//      PREP_DINNER_ROOM
int					ft_bouncer(int ac, char **av);
t_table				*ft_lay_table(int ac, char **av);
t_philo				*ft_introduce_guests(t_table *table, char **av);
void				ft_assign_forks(t_table *table, int pos);

//      ROUTINES
void				*ft_waiter_routine(void *args);
void				*ft_dinner_routine(void *args);
int					ft_take_forks(t_philo *philo);
void				ft_eat(t_philo *philo);

//      DINNER_STAFF_ASSIGNMENT
int					ft_check_death(t_table *table, t_philo philo, int dishes,
						int last_eat);
void				ft_check_dishes(t_table *table, int *dead);
void				ft_broadcasting(t_philo *philo, char *msg, int flag);
int					ft_current_time(t_philo *philo);
int					ft_time_to_ms(struct timeval time);

//      UTILS
int					ft_isint(char *str);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);

#endif
