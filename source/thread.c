/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   thread.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:47:03 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 16:48:31 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* thread_error_handler:
	* Handles pthread thread-related errors.
	* Prints descriptive messages for creation or join failures.
	* Returns EXIT_SUCCESS if no error or an error code otherwise.
*/
int	thread_error_handler(int status, t_thread_operation operation)
{
	if (status == 0)
		return (EXIT_SUCCESS);
	if (status == EAGAIN)
		return (print_msg("No resources to create another thread.\n",
				NULL, EXIT_FAILURE));
	else if (status == EINVAL && operation == THREAD_JOIN)
		return (print_msg("Thread is not a joinable thread.\n",
				NULL, EXIT_FAILURE));
	else if (status == EINVAL && operation == THREAD_CREATE)
		return (print_msg("Thread creation failed: invalid args.\n",
				NULL, EXIT_FAILURE));
	else if (status == ESRCH)
		return (print_msg("No thread with the ID specified could be found.\n",
				NULL, EXIT_FAILURE));
	else if (status == EDEADLK)
		return (print_msg("A deadlock was detected.\n",
				NULL, EXIT_FAILURE));
	else
		return (print_msg("Unknown error.\n", NULL, EXIT_FAILURE));
	return (print_msg("Unknown thread error.\n", NULL, EXIT_FAILURE));
}

/* thread_operator:
	* Performs thread operations such as create or join.
	* Encapsulates pthread_create and pthread_join with error checking.
	* Returns the result handled by thread_error_handler().
*/
int	thread_operator(pthread_t *thread, void *(*routine)(void *), void *data,
		t_thread_operation operation)
{
	int		status;

	status = 0;
	if (operation == THREAD_CREATE)
		status = pthread_create(thread, NULL, routine, data);
	else if (operation == THREAD_JOIN)
		status = pthread_join(*thread, NULL);
	else
		return (print_msg("Wrong operation code for thread_operator.\n",
				NULL, EXIT_FAILURE));
	return (thread_error_handler(status, operation));
}
