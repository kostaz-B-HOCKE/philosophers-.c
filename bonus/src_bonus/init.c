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

#include "philo.h"

int	create_philo(t_all *_all)
{
	int	i;

	i = -1;
	_all->philo = malloc(sizeof(t_philo) * _all->num_phil);
	if (!_all->philo)
		return (1);
	while (++i < _all->num_phil)
	{
		_all->philo[i].id = i + 1;
		_all->philo[i].last_eat = 0;
		_all->philo[i].nbr_of_ate = 0;
		_all->philo[i].all_st = _all;
	}
	return (0);
}

void	create_sem(t_all *_all)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("main_lock");
	_all->forks = sem_open("forks", O_CREAT | O_EXCL, S_IRWXU, _all->num_phil);
	_all->write = sem_open("write", O_CREAT | O_EXCL, S_IRWXU, 1);
	_all->main_lock = sem_open("main_lock", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (_all->nbr_to_eat > 0)
	{
		sem_unlink("eat_con");
		_all->eat_con = sem_open("eat_con", O_CREAT | O_EXCL, S_IRWXU, 0);
	}
}

void	*eat_func(void *arg)
{
	t_all	*_all;
	int		i;

	_all = (t_all *)arg;
	i = -1;
	sem_wait(_all->write);
	while (++i < _all->num_phil)
	{
		sem_post(_all->write);
		sem_wait(_all->eat_con);
		sem_wait(_all->write);
	}
	sem_post(_all->main_lock);
	return (NULL);
}

int	check_eat(t_all *_all)
{
	if (_all->nbr_to_eat > 0)
	{
		if (pthread_create(&_all->check_eat, NULL, &eat_func, _all))
			return (1);
		pthread_detach(_all->check_eat);
	}
	return (0);
}

int	me_init(int argc, char **argv, t_all *_all)
{
	_all->num_phil = ft_atoi(argv[1]);
	_all->time_to_die = ft_atoi(argv[2]);
	_all->time_to_eat = ft_atoi(argv[3]);
	_all->time_to_sleep = ft_atoi(argv[4]);
	_all->nbr_to_eat = -1;
	if (argc == 6)
		_all->nbr_to_eat = ft_atoi(argv[5]);
	_all->flag_dead = 0;
	create_sem(_all);
	if (create_philo(_all))
		return (1);
	if (check_eat(_all))
		return (1);
	return (0);
}
