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

void	one_philo(t_all *_all)
{
	_all->start_time = get_time();
	print_mutex(&_all->philo[0], _all, "has taken a fork");
	ft_delay(_all->time_to_die);
	print_mutex(&_all->philo[0], _all, "is dead");
}

int	me_pthreads(t_all *_all)
{
	int	i;

	i = -1;
	_all->start_time = get_time();
	while (++i < _all->number_phil)
	{
		if (pthread_create(&_all->philo[i].th, NULL, routine,
				(void *)&_all->philo[i]))
		{
			printf("Error pthread_creadte routine\n");
			return (1);
		}
		ft_delay(1);
	}
	i = -1;
	while (++i < _all->number_phil)
	{
		if (pthread_join(_all->philo[i].th, NULL))
		{
			printf("Error pthread_join routine\n");
			return (1);
		}
	}
	return (0);
}

void	free_struct_all(t_all *_all)
{
	int	i;

	i = -1;
	while (++i < _all->number_phil)
		pthread_mutex_destroy(&_all->plug[i]);
	free(_all->plug);
	free(_all->philo);
}

int	start_philosof(int argc, char **argv)
{
	t_all	_all;

	if (validation(argc, argv) != 2)
		return (1);
	if (me_init(argc, argv, &_all) == 1)
		return (1);
	if (_all.number_phil == 1)
	{
		one_philo(&_all);
		free_struct_all(&_all);
		return (0);
	}
	else
	{
		if (me_pthreads(&_all) == 1)
			return (1);
	}
	free_struct_all(&_all);
	return (0);
}

int	main(int argc, char **argv)
{
	start_philosof(argc, argv);
}
