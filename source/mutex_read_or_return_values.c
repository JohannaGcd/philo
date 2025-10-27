/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_read_or_return_values.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:40:43 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 10:58:06 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// check if i use each function or if i can delete one 
void	write_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);

}

bool	return_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}

void	write_int(pthread_mutex_t *mutex, int *dest, int value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);
}

int	return_int(pthread_mutex_t *mutex, int *value)
{
	bool	ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}

void	write_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);
}

long	return_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}