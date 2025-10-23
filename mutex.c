#include "philo.h"

static void	mutex_error_handler(t_mutex_operation operator, int status)
{
	if (status == 0)
		return ;
	else if (EINVAL == status && (operator == MUTEX_LOCK || operator == MUTEX_UNLOCK))
		warning_msg("Invalid mutex: the value specified by mutex is invalid.\n", NULL, 1);
	else if (EINVAL == status && operator == MUTEX_CREATE)
		warning_msg("Invalid attributes: the value specified by attr is invalid.\n", NULL, 1);
	else if (EDEADLK == status)
		warning_msg("Deadlock risk detected.\n", NULL, 1);
	else if (EPERM == status)
		warning_msg("Thread does not hold the mutex lock.\n", NULL, 1);
	else if (ENOMEM == status)
		warning_msg("Insufficient memory to initialize mutex.\n", NULL, 1);
	else if (EBUSY == status)
		warning_msg("Mutex is locked", NULL, 1);
	else
		warning_msg("Unknown mutex error.\n", NULL, 1);
	exit(EXIT_FAILURE);
}

/* mutex_operator

*/
void mutex_operator(pthread_mutex_t *mutex, t_mutex_operation operation)
{
	int status;

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
	{
		warning_msg("Wrong operation code for mutex.\n", NULL, 1);
		exit(EXIT_FAILURE); // use a safe exit function to clean up
	}
	mutex_error_handler(operation, status);
}