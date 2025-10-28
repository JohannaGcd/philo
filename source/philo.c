/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:46:53 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/28 15:36:53 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* philo_eat_then_sleep:
	* Handles the eating and sleeping cycle for one philosopher.
	* Locks both forks before eating to ensure exclusive access.
	* Updates last meal time and meal count safely under mutex.
	* After eating, unlocks forks and switches to sleeping state.
 */
static void	philo_eat_then_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->fork_mutex);
	write_status(philo, false, GOT_FIRST_FORK);
	pthread_mutex_lock(&philo->fork_two->fork_mutex);
	write_status(philo, false, GOT_SECOND_FORK);
	write_status(philo, false, EATING);
	write_long(&philo->meal_time_lock, &philo->last_meal_time,
		get_time_in_ms());
	philo_sleep(philo->table, philo->table->time_to_eat);
	if (has_dinner_stopped(philo->table) == false)
		write_int(&philo->meal_time_lock, &philo->meals_nbr, philo->meals_nbr
			+ 1);
	pthread_mutex_unlock(&philo->fork_one->fork_mutex);
	pthread_mutex_unlock(&philo->fork_two->fork_mutex);
	write_status(philo, false, SLEEPING);
	philo_sleep(philo->table, philo->table->time_to_sleep);
}

/* philo_sleep:
	* Makes the philosopher sleep for a given duration in ms.
	* Continuously checks if the dinner has ended to stop early.
	* Uses short usleep intervals to remain responsive to death checks.
 */
void	philo_sleep(t_table *table, time_t time_to_sleep)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + time_to_sleep;
	while (get_time_in_ms() < wake_up)
	{
		if (has_dinner_stopped(table))
			break ;
		usleep(1000);
	}
}

/* single_philo:
	* Handles the special case with only one philosopher.
	* Takes one fork, - but cannot pick the second one (since it doesn't exist)
	* waits until time_to_die expires, and dies.
 */
static void	*single_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_one->fork_mutex);
	write_status(philo, false, GOT_FIRST_FORK);
	philo_sleep(philo->table, philo->table->time_to_die);
	write_status(philo, false, DIED);
	pthread_mutex_unlock(&philo->fork_two->fork_mutex);
	return (NULL);
}

/* philo_think:
	* Computes the time the philosopher should spend thinking.
	* The delay helps avoid simultaneous fork grabs.
	* Locks meal_time to calculate remaining safe thinking time.
	* Limits extreme values to keep timing realistic.
 */
static void	philo_think(t_philo *philo, bool delay)
{
	time_t	thinking_time;

	pthread_mutex_lock(&philo->meal_time_lock);
	thinking_time = (philo->table->time_to_die - (get_time_in_ms()
				- philo->last_meal_time) - philo->table->time_to_eat) / 3;
	pthread_mutex_unlock(&philo->meal_time_lock);
	if (thinking_time < 0)
		thinking_time = 0;
	if (thinking_time == 0 && delay == true)
		thinking_time = 1;
	if (thinking_time > 600)
		thinking_time = 200;
	if (delay == false)
		write_status(philo, false, THINKING);
	philo_sleep(philo->table, thinking_time);
}

/* philo_routine:
	* Main loop executed by each philosopher thread.
	* Initializes last meal time and synchronizes start with others.
	* If only one philosopher exists, runs single_philo().
	* Otherwise loops through eating, sleeping, and thinking
	* until the dinner is stopped by the monitor thread ('faucheuse').
 */
void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	write_long(&philo->meal_time_lock, &philo->last_meal_time,
		philo->table->start_time);
	coordinate_start(philo->table->start_time);
	if (philo->table->time_to_die == 0)
		return (NULL);
	if (philo->table->philo_nbr == 1)
		return (single_philo(philo));
	else if (philo->philo_id % 2)
		philo_think(philo, true);
	while (has_dinner_stopped(philo->table) == false)
	{
		philo_eat_then_sleep(philo);
		philo_think(philo, false);
	}
	return (NULL);
}
