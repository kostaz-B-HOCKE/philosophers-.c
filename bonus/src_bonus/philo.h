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
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>

typedef struct s_philo
{
	int				id;
	int				nbr_of_ate;
	time_t			last_eat;
	pthread_t		control;
	pid_t			pid;
	struct s_all	*all_st;
}		t_philo;

typedef struct s_all
{
	int				num_phil;
	time_t			time_to_eat;
	time_t			time_to_die;
	time_t			time_to_sleep;
	int				nbr_to_eat;
	int				flag_dead;
	time_t			start_time;
	sem_t			*write;
	sem_t			*forks;
	sem_t			*main_lock;
	sem_t			*eat_con;
	pthread_t		check_eat;
	t_philo			*philo;
}	t_all;

int		validation(int argc, char **argv);
int		ft_atoi(char *s);
time_t	get_time(void);
time_t	delta_time(time_t time);
void	ft_delay(time_t sec);
int		check_death(t_philo *philo, t_all *_all);
int		me_init(int argc, char **argv, t_all *_all);
int		eating(t_philo *philo, t_all *_all);
int		sleeping(t_philo *philo, t_all *_all);
int		thinkig(t_philo *philo, t_all *_all);
int		print_sem(t_philo *philo, t_all *_all, char *str);
void	free_inlink(t_all *_all);

#endif
