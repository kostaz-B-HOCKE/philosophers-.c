/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:50:51 by                   #+#    #+#             */
/*   Updated: 2022/03/16 14:53:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_inlink(t_all *_all)
{
	sem_close(_all->forks);
	sem_unlink("forks");
	sem_close(_all->write);
	sem_unlink("write");
	sem_close(_all->main_lock);
	sem_unlink("main_lock");
	if (_all->nbr_to_eat > 0)
	{
		sem_close(_all->eat_con);
		sem_unlink("eat_con");
	}
}

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

void	ft_delay(time_t sec)
{
	long	time;

	time = get_time();
	usleep(sec * 920);
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
		_all->flag_dead = 1;
		print_sem(philo, _all, "is dead");
		return (1);
	}
	return (0);
}
