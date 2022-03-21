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

int	print_sem(t_philo *philo, t_all *_all, char *str)
{
	sem_wait(_all->write);
	printf("%-10ld %d %s\n", delta_time(_all->start_time), philo->id, str);
	sem_post(_all->write);
	return (0);
}

int	eating(t_philo *philo, t_all *_all)
{
	if (philo->nbr_of_ate == _all->nbr_to_eat)
		return (1);
	sem_wait(_all->forks);
	sem_wait(_all->forks);
	print_sem(philo, _all, "has taken a fork");
	print_sem(philo, _all, "has taken a fork");
	print_sem(philo, _all, "is eating");
	philo->last_eat = get_time();
	if (philo->nbr_of_ate >= 0)
		philo->nbr_of_ate++;
	if (philo->nbr_of_ate == _all->nbr_to_eat)
		sem_post(_all->eat_con);
	ft_delay(_all->time_to_eat);
	sem_post(_all->forks);
	sem_post(_all->forks);
	return (0);
}

int	sleeping(t_philo *philo, t_all *_all)
{
	print_sem(philo, _all, "is sleeping");
	ft_delay(_all->time_to_sleep);
	return (0);
}

int	thinkig(t_philo *philo, t_all *_all)
{
	print_sem(philo, _all, "is thinkig");
	return (0);
}
