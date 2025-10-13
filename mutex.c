#include "philo.h"

/* mutex_error_handler: --> update
	returns the appropriate error code for thread operations.
	And calls warning_msg to exit the program.
*/
static void	mutex_error_handler(t_mutex_operation *operator, int status) // check if warning_msg appropriate
{
	if (status == 0)
		return ;
	else if (EINVAL == status && (operator == LOCK || operator == UNLOCK))
		return (warning_msg("The value specified by mutex is invalid", NULL, 1)); // check exit number
	else if (EINVAL == status && operator == INIT)
		return (warning_msg("Value specified by attr is invalid", NULL, 1)); // what is attr
	else if (EDEADLK == status)
		return (warning_msg("Deadlock risk", NULL, 1));
	else if (EPERM == status)
		return (warning_msg("Current thread does not hold a lock on mutex", NULL, 1));
	else if (ENOMEM == status)
		return (warning_msg("Insufficient memory", NULL, 1));
	else if (EBUSY == status)
		return (warning_msg("Mutex is locked", NULL, 1));

}

/* mutex_operator
	Using the enum table for each operation,
	this functions centralizes all mutex operations.
	and exits upon error, using mutex_error_handler.
*/
void	mutex_operator(pthread_mutex_t *mutex, t_mutex_operation operation)
{
	if (operation == LOCK)
		mutex_error_handler(pthread_mutex_lock(mutex));
	else if (operation == UNLOCK)
		mutex_error_handler(pthread_mutex_unlock(mutex));
	else if (operation == CREATE)
		mutex_error_handler(pthread_mutex_init(mutex, NULL));
	else if (operation == CDESTROY)
		mutex_error_handler(pthread_mutex_destroy(mutex));
	else
		warning_message("Wrong operation code for mutex.\n", NULL, 1); // check if this works
}