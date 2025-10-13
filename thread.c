#include "philo.h"

static void	thread_error_handler(t_mutex_operation *operator, int status) // check if warning_msg appropriate

void	thread_operator(pthread_mutex_t *mutex, t_mutex_operation operation)
{
	if (operation == CREATE)
		pthread_create()
}