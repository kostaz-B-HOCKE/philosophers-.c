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

void	*control(void *arg)
{
	t_all	*part_all;
	t_philo	*philo;

	philo = (t_philo *)arg;
	part_all = philo->_all;
	while (!part_all->flag_dead)
	{
		if (part_all->nbr_to_eat == philo->nbr_of_ate)
			break ;
		if (check_death(philo, part_all))
			break ;
	}
	return (NULL);
}

int	routine_arction(t_philo *philo, t_all *part_all)
{
	if (eating(philo, part_all))
		return (1);
	if (part_all->nbr_to_eat != philo->nbr_of_ate)
	{
		if (sleep_philo(philo, part_all))
			return (1);
		if (thinking(philo, part_all))
			return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_all	*part_all;

	philo = (t_philo *)arg;
	part_all = philo->_all;
	if (pthread_create(&philo->control, NULL, control, (void *)philo))
		return (NULL);
	pthread_detach(philo->control);
	while (!part_all->flag_dead)
	{
		if (part_all->nbr_to_eat == philo->nbr_of_ate)
			break ;
		if (routine_arction(philo, part_all))
			break ;
	}
	return (NULL);
}
