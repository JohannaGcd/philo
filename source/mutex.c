/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mutex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:42:00 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 16:47:47 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* mutex_error_handler:
	* Handles and reports pthread_mutex error codes.
	* Prints a readable message describing the failure.
	* Returns EXIT_SUCCESS if no error or prints details otherwise.
*/
static int	mutex_error_handler(t_mutex_operation operator, int status)
{
	if (status == 0)
		return (EXIT_SUCCESS);
	else if (EINVAL == status && (operator == MUTEX_LOCK
			|| operator == MUTEX_UNLOCK))
		return (print_msg("Invalid mutex: \
			the value specified by mutex is invalid.\n",
				NULL, EXIT_FAILURE));
	else if (EINVAL == status && operator == MUTEX_CREATE)
		return (print_msg("Invalid attributes: \
			the value specified by attr is invalid.\n",
				NULL, EXIT_FAILURE));
	else if (EDEADLK == status)
		return (print_msg("Deadlock risk detected.\n", NULL, 1));
	else if (EPERM == status)
		return (print_msg("Thread does not hold the mutex lock.\n", NULL, 1));
	else if (ENOMEM == status)
		return (print_msg("Insufficient memory to initialize mutex.\n", NULL,
				1));
	else if (EBUSY == status)
		return (print_msg("Mutex is locked", NULL, 1));
	else
		return (print_msg("Unknown mutex error.\n", NULL, 1));
	return (print_msg("Unknown mutex error\n", NULL, EXIT_FAILURE));
}

/* mutex_operator:
	* Performs a mutex operation safely (lock, unlock, create, destroy).
	* Handles all pthread_mutex calls and centralizes error checking.
	* Returns the status code processed by mutex_error_handler().
*/
int	mutex_operator(pthread_mutex_t *mutex, t_mutex_operation operation)
{
	int	status;

	status = 0;
	if (operation == MUTEX_LOCK)
		status = pthread_mutex_lock(mutex);
	else if (operation == MUTEX_UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (operation == MUTEX_CREATE)
		status = pthread_mutex_init(mutex, NULL);
	else if (operation == MUTEX_DESTROY)
		status = pthread_mutex_destroy(mutex);
	else
		return (print_msg("Wrong op code for mutex.\n", NULL, EXIT_FAILURE));
	return (mutex_error_handler(operation, status));
}
