#include "philo.h"

static void	thread_error_handler(int status, t_mutex_operation operation) // check if warning_msg with exit nbr is appropriate here
{
	if (status == 0)
		return;
	if (status == EAGAIN)
		warning_msg("No resources to create another thread.\n", NULL, 1);
	else if (status == EINVAL && operation == THREAD_JOIN)
		warning_msg("Thread is not a joinable thread.\n", NULL, 1);
	else if (status == EINVAL && operation == THREAD_CREATE)
		warning_msg("Thread creation failed: invalid argument or attributes.\n", NULL, 1);
	else if (status == ESRCH)
		warning_msg("No thread with the ID specified could be found.\n", NULL, 1);
	else if (status == EDEADLK)
		warning_msg("A deadlock was detected.\n", NULL, 1);
	else
		warning_msg("Unknown error.\n", NULL, 1);
	exit(EXIT_FAILURE);
}

void	thread_operator(pthread_t *thread, void *(*routine)(void *), void *data, t_thread_operation operation)
{
	int status;

	status = 0;
	if (operation == THREAD_CREATE)
		status = pthread_create(thread, NULL, routine, data);
	else if (operation == THREAD_JOIN)
		status = pthread_join(*thread, NULL);
	else
	{
		warning_msg("Wrong operation code for thread_operator", NULL, 1);
		exit(EXIT_FAILURE); // insert freeing function before exiting
	}
	thread_error_handler(status, operation);
}