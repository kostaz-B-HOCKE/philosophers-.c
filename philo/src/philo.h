/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:50:51 by                   #+#    #+#             */
/*   Updated: 2022/01/23 13:39:56 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <sys/time.h>

# include <time.h>

typedef struct s_philo
{
	int				id;
	int				id_left;
	int				id_r;
	int				nbr_of_ate;
	time_t			last_eat;
	pthread_t		control;
	pthread_t		th;
	struct s_all	*_all;
}		t_philo;

typedef struct s_all
{
	int				number_phil;
	time_t			time_to_eat;
	time_t			time_to_die;
	time_t			time_to_sleep;
	int				nbr_to_eat;
	int				flag_dead;
	time_t			start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	*plug;
	t_philo			*philo;
}	t_all;

int		validation(int argc, char **argv);
int		me_init(int argc, char **argv, t_all *_all);
int		print_mutex(t_philo *philo, t_all *_all, char *str);
int		check_death(t_philo *philo, t_all *_all);
int		eating(t_philo *philo, t_all *_all);
int		sleep_philo(t_philo *philo, t_all *_all);
int		thinking(t_philo *philo, t_all *_all);
void	one_philo(t_all *_all);
void	*routine(void *arg);
int		routine_arction(t_philo *philo, t_all *part_all);
void	*control(void *arg);
int		me_pthreads(t_all *_all);
time_t	get_time(void);
void	ft_delay(time_t sec);
time_t	delta_time(time_t time);

//libft
int		ft_atoi(char *s);
#endif
