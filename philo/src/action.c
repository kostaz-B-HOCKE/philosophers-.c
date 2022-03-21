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

int	print_mutex(t_philo *philo, t_all *_all, char *str)
{
	if (_all->flag_dead)
		return (1);
	pthread_mutex_lock(&_all->write);
	if (_all->flag_dead)
	{
		pthread_mutex_unlock(&_all->write);
		return (1);
	}
	printf("%-10ld %d %s\n", delta_time(_all->start_time), philo->id, str);
	pthread_mutex_unlock(&_all->write);
	return (0);
}

int	eating(t_philo *philo, t_all *_all)
{
	pthread_mutex_lock(&_all->plug[philo->id_left]);
	if (print_mutex(philo, _all, "has taken a fork!"))
		return (1);
	pthread_mutex_lock(&_all->plug[philo->id_r]);
	if (print_mutex(philo, _all, "has taken a fork!"))
		return (1);
	if (print_mutex(philo, _all, "is eating"))
		return (1);
	philo->last_eat = get_time();
	ft_delay(_all->time_to_eat);
	philo->nbr_of_ate++;
	pthread_mutex_unlock(&_all->plug[philo->id_left]);
	pthread_mutex_unlock(&_all->plug[philo->id_r]);
	return (0);
}

int	sleep_philo(t_philo *philo, t_all *_all)
{
	if (print_mutex(philo, _all, "is sleep"))
		return (1);
	ft_delay(_all->time_to_sleep);
	return (0);
}

int	thinking(t_philo *philo, t_all *_all)
{
	if (print_mutex(philo, _all, "is thinking"))
		return (1);
	return (0);
}
