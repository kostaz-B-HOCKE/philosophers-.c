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

void	*ccontrol(void *arg)
{
	t_all	*_all;
	t_philo	*philo;

	philo = (t_philo *)arg;
	_all = philo->all_st;
	while (!_all->flag_dead)
	{
		if (check_death(philo, _all))
			break ;
	}
	sem_post(_all->main_lock);
	sem_wait(_all->write);
	exit(EXIT_FAILURE);
}

void	routinee(t_philo *philo, t_all *_all)
{
	if (pthread_create(&philo->control, NULL, ccontrol, (void *)philo))
		exit(EXIT_FAILURE);
	pthread_detach(philo->control);
	while (!_all->flag_dead)
	{
		if (eating(philo, _all))
			break ;
		sleeping(philo, _all);
		thinkig(philo, _all);
	}
	exit(EXIT_SUCCESS);
}

int	start_philos(t_all *_all)
{
	int	i;

	i = 0;
	_all->start_time = get_time();
	while (i < _all->num_phil)
	{
		_all->philo[i].pid = fork();
		if (_all->philo[i].pid == -1)
		{
			while (--i >= 0)
				kill(_all->philo[i].pid, SIGKILL);
			return (1);
		}
		else if (_all->philo[i].pid == 0)
			routinee(&_all->philo[i], _all);
		i++;
	}
	sem_wait(_all->main_lock);
	return (0);
}

void	one_philo(t_all *_all)
{
	_all->start_time = get_time();
	print_sem(&_all->philo[0], _all, "has taken a fork");
	ft_delay(_all->time_to_die);
	print_sem(&_all->philo[0], _all, "is dead");
	free_inlink(_all);
	free(_all->philo);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_all	_all;

	if (validation(argc, argv))
		return (1);
	if (me_init(argc, argv, &_all))
		return (1);
	if (_all.num_phil == 1)
	{
		one_philo(&_all);
		return (0);
	}
	else
		start_philos(&_all);
	free_inlink(&_all);
	free(_all.philo);
}
