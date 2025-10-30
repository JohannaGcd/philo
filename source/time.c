/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/29 15:24:15 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/30 12:43:36 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* get_time_in_us:
*	Returns the current system time in microseconds.
*	Uses gettimeofday() for high-resolution timing.
*	Used for precise sleep and time tracking in philosophers.
*/
static long	get_time_in_us(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 10000000) + time.tv_usec);
}

/* precise_usleep:
	* Sleeps for the given duration (in ms) with high precision.
	* Uses short usleep calls and time checks to avoid oversleeping.
	* Regularly tests if the dinner has ended to exit early.
*/
void	precise_usleep(t_table *table, time_t time_to_sleep)
{
	time_t	start;
	time_t	elapsed;

	start = get_time_in_us();
	while (1)
	{
		if (has_dinner_stopped(table))
			return ;
		elapsed = (get_time_in_us() - start) / 1000;
		if (elapsed >= time_to_sleep)
			return ;
		usleep(time_to_sleep * 1000);
	}
}

void	micro_usleep(time_t microseconds)
{
	time_t		start;

	start = get_time_in_us();
	while (get_time_in_us() - start < microseconds)
		usleep(100);
}
