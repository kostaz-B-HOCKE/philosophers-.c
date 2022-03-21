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

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	ft_delay(time_t sec)
{
	time_t	time;

	time = get_time();
	usleep(sec * 1000);
	while (get_time() < time + sec)
		usleep(50);
}

time_t	delta_time(time_t time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

int	check_death(t_philo *philo, t_all *_all)
{
	time_t	time;

	time = delta_time(philo->last_eat);
	if (time > _all->time_to_die)
	{
		print_mutex(philo, _all, "is dead");
		_all->flag_dead = 1;
		return (1);
	}
	return (0);
}
