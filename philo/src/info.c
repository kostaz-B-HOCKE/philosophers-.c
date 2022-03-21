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

int	create_plugs(t_all *_all)
{
	int	i;

	i = -1;
	_all->plug = malloc(sizeof(pthread_mutex_t) * _all->number_phil);
	if (!_all->plug)
		return (1);
	while (++i < _all->number_phil)
	{
		if (pthread_mutex_init(&_all->plug[i], NULL))
		{
			printf("Error mutex_init\n");
			return (1);
		}
	}
	return (0);
}

int	create_philos(t_all *_all)
{
	int	i;

	i = -1;
	_all->philo = malloc(sizeof(t_philo) * _all->number_phil);
	if (!_all->philo)
		return (1);
	while (++i < _all->number_phil)
	{
		_all->philo[i].id = i + 1;
		_all->philo[i].id_left = i;
		_all->philo[i].id_r = (i + 1) % _all->number_phil;
		_all->philo[i].last_eat = 0;
		_all->philo[i]._all = _all;
		_all->philo[i].nbr_of_ate = 0;
	}
	return (0);
}

int	me_init(int argc, char **argv, t_all *_all)
{
	_all->number_phil = ft_atoi(argv[1]);
	_all->time_to_die = ft_atoi(argv[2]);
	_all->time_to_eat = ft_atoi(argv[3]);
	_all->time_to_sleep = ft_atoi(argv[4]);
	_all->nbr_to_eat = -1;
	if (argc == 6)
		_all->nbr_to_eat = ft_atoi(argv[5]);
	_all->flag_dead = 0;
	if (create_plugs(_all) == 1)
		return (1);
	if (create_philos(_all) == 1)
		return (1);
	return (0);
}
