/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   faucheuse.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:37:21 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/29 15:30:37 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* kill_philo:
	* Checks if a philosopher has exceeded time_to_die.
	* If the time since the last meal is too long, marks simulation as ended.
	* Prints the death message and returns true if the philosopher died.
	* Returns false if the philosopher is still alive.
*/
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

/* has_dinner_stopped:
	* Returns the current value of the simulation stop flag.
	* Reads the 'end' variable safely using the table mutex.
	* Used by all threads to check if they should stop running.
*/
bool	has_dinner_stopped(t_table *table)
{
	return (return_bool(&table->table_lock, &table->end));
}

/* must_stop_dinner:
	* Checks all philosophers to decide if the dinner must stop.
	* Locks each philosopher’s meal mutex to read meal data safely.
	* Stops the dinner immediately if a philosopher has died.
	* If a meal limit is set, checks if all philosophers reached it.
	* Sets the 'end' flag and returns true when the simulation must end.
*/
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

/* faucheuse:
	* Monitor thread that supervises the simulation.
	* Waits for the start signal, then checks philosophers in a loop.
	* Calls must_stop_dinner() to detect death or completion.
	* Sets the end flag and stops the loop when a stop condition occurs.
	* Sleeps briefly each loop to reduce CPU usage and stay responsive.
*/
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
		micro_usleep(700);
	}
	return (NULL);
}
