#include "philo.h"

void	write_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);

}

bool	return_bool(pthread_mutex_t *mutex, bool *value)
{
	bool ret;

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
	bool ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}

// check if i really need longs, or if i can use ints

void	write_long(pthread_mutex_t *mutex, long *dest, long value)
{
	mutex_operator(mutex, MUTEX_LOCK);
	*dest = value;
	mutex_operator(mutex, MUTEX_UNLOCK);
}

long	return_long(pthread_mutex_t *mutex, long *value)
{
	long ret;

	mutex_operator(mutex, MUTEX_LOCK);
	ret = *value;
	mutex_operator(mutex, MUTEX_UNLOCK);
	return (ret);
}