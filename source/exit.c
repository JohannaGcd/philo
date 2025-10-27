/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:09:05 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 16:44:33 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* destroy_mutexes:
	* Destroys all mutexes used in the program.
	* Frees resources tied to fork and philosopher locks.
	* Also destroys the main table mutex at the end.
*/
void	destroy_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i].fork_mutex);
		pthread_mutex_destroy(&table->philos[i].meal_time_lock);
		i++;
	}
	pthread_mutex_destroy(&table->table_lock);
}

/* free_table:
	* Frees all dynamically allocated memory in the table.
	* Releases memory for forks, philosophers, and the table itself.
	* Returns NULL so it can be used directly in error returns.
*/
void	*free_table(t_table *table)
{
	if (!table)
		return (NULL);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
	free(table);
	return (NULL);
}

/* print_msg:
	* Prints an error or status message to the console.
	* If 'detail' is NULL, prints the message as is.
	* Returns the given exit code for error handling.
*/
int	print_msg(char *str, char *detail, int exit_nbr)
{
	if (!detail)
		printf(str, STR_PROG_NAME);
	else
		printf(str, STR_PROG_NAME, detail);
	return (exit_nbr);
}

/* err_null:
	* Prints an error message and frees the table if needed.
	* Returns NULL for use in functions that return a pointer.
	* Used when a memory allocation or setup step fails.
*/
void	*err_null(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(NULL);
	print_msg(str, details, EXIT_FAILURE);
	return (NULL);
}

/* err_exit:
	* Prints an error message and frees the table if it exists.
	* Returns the exit code from print_msg for easy propagation.
*/
int	err_exit(char *str, char *details, t_table *table)
{
	if (table != NULL)
		free_table(table);
	return (print_msg(str, details, EXIT_FAILURE));
}
