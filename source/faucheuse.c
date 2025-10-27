/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   faucheuse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:37:21 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 14:09:31 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	kill_philo(t_philo *philo)
{
	time_t	time;

	time = get_time_in_ms();
	if ((time - philo->last_meal_time) >= philo->table->time_to_die)
	{
		write_bool(&philo->table->table_lock, &philo->table->end, true);
		write_status(philo, true, DIED);
		return (true);
	}
	return (false);
}

bool	has_dinner_stopped(t_table *table)
{
	return (return_bool(&table->table_lock, &table->end));
}

bool	must_stop_dinner(t_table *table)
{
	int		i;
	bool	all_philo_full;

	all_philo_full = true;
	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_lock(&table->philos[i].meal_time_lock);
		if (kill_philo(&table->philos[i]))
			return (pthread_mutex_unlock(&table->philos[i].meal_time_lock),
				true);
		if (table->must_eat != -1)
		{
			if (table->philos[i].meals_nbr < table->must_eat)
				all_philo_full = false;
		}
		pthread_mutex_unlock(&table->philos[i].meal_time_lock);
		i++;
	}
	if (table->must_eat != -1 && all_philo_full == true)
	{
		write_bool(&table->table_lock, &table->end, true);
		return (true);
	}
	return (false);
}

void	*faucheuse(void *data)
{
	t_table		*table;

	table = (t_table *)data;
	if (table->must_eat == 0)
		return (NULL);
	write_bool(&table->table_lock, &table->end, false);
	coordinate_start(table->start_time);
	while (true)
	{
		if (must_stop_dinner(table) == true)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
