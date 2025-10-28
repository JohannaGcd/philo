/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:48:46 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/28 15:46:46 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* print_status:
	* Formats and prints a status message for a philosopher.
	* Displays timestamp, philosopher ID, and activity text.
*/
static void	print_status(t_philo *philo, char *s)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->philo_id, s);
}

/* write_status:
	* Prints a philosopher’s current action in a thread-safe way.
	* Locks the table mutex to prevent overlapping outputs.
	* Ignores messages from philosophers after the dinner ends.
*/
void	write_status(t_philo *philo, bool faucheuse_info, t_status status)
{
	if (has_dinner_stopped(philo->table) == true && faucheuse_info == false)
		return ;
	pthread_mutex_lock(&philo->table->table_lock);
	if (status == DIED)
		print_status(philo, "died");
	else if (status == EATING)
		print_status(philo, "is eating");
	else if (status == SLEEPING)
		print_status(philo, "is sleeping");
	else if (status == THINKING)
		print_status(philo, "is thinking");
	else if (status == GOT_FIRST_FORK || status == GOT_SECOND_FORK)
		print_status(philo, "has taken a fork");
	pthread_mutex_unlock(&philo->table->table_lock);
}

/* coordinate_start:
	* Synchronizes thread start times.
	* Busy-waits until the global start timestamp is reached.
	* Ensures all threads begin the simulation together.
*/
void	coordinate_start(time_t start)
{
	while (get_time_in_ms() < start)
		continue ;
}

/* get_time_in_ms:
	* Returns the current system time in milliseconds.
	* Used for timing actions and measuring philosopher delays.
*/
time_t	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/* precise_usleep:
	* Sleeps for the given duration (in ms) with high precision.
	* Uses short sleep intervals and time checks to avoid oversleeping.
	* Regularly tests if the dinner has ended to exit early.
*/
// void	precise_usleep(t_table *table, time_t time_to_sleep)
// {
// 	time_t	start;
// 	time_t	now;

// 	start = get_time_in_ms();
// 	time_to_sleep = time_to_sleep * 1000;
// 	while (1)
// 	{
// 		if (has_dinner_stopped(table))
// 			break ;
// 		now = get_time_in_ms();
// 		if (now - start >= time_to_sleep)
// 			break ;
// 		usleep(200);
// 	}
// }
