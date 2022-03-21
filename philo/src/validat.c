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

static int	is_digit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int	r;
	int	sig;

	sig = 1;
	r = 0;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s && (*s == '-' || *s == '+'))
	{
		if (*s == '-')
			sig = -1;
		s++;
	}
	while (*s && (*s >= '0' && *s <= '9'))
	{
		r = r * 10 + *s - '0';
		s++;
	}
	return (r * sig);
}

int	validation(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("argumet Error\n");
		return (1);
	}
	while (i < argc)
	{
		if (!(is_digit(argv[i])))
		{
			printf("argumet Error\n");
			return (1);
		}
		i++;
	}
	return (2);
}
