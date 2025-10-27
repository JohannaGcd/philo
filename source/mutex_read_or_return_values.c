/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex_read_or_return_values.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:40:43 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 16:46:41 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// TODO check if i use each function or if i can delete one 



/* write_bool:
	* Sets a boolean value safely under a mutex lock.
	* Prevents race conditions when updating shared flags.
*/
void	write_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);
}

/* return_bool:
	* Reads a boolean value safely under a mutex lock.
	* Used to check shared flags like the simulation end flag.
*/
bool	return_bool(pthread_mutex_t *mutex, bool *value)
{
	bool	ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}

/* write_int:
	* Writes an integer value safely under a mutex lock.
	* Used for counters such as meal counts.
*/
void	write_int(pthread_mutex_t *mutex, int *dest, int value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);
}

/* write_long:
	* Writes a long integer to a shared variable under mutex protection.
	* Ensures thread-safe updates for time values.
*/
void	write_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);
}

/* return_long:
	* Reads a long integer safely under mutex protection.
	* Used to access shared time-related values.
*/
long	return_long(pthread_mutex_t *mutex, long *value)
{
	long	ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}
/*int	return_int(pthread_mutex_t *mutex, int *value)
{
	bool	ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}*/