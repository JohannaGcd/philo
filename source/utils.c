/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:48:46 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 10:56:00 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status(t_philo *philo, char *s)
{
	printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time,
		philo->philo_id, s);
}

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

void	coordinate_start(time_t start)
{
	while (get_time_in_ms() < start)
		continue ;
}

time_t	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
