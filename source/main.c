/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 14:07:59 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/29 15:30:46 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// TODO: 0 check: double check if this 
//should be done in philo_routine or if its fine here

/* start_dinner:
	* Starts the philosopher simulation by creating one thread per philosopher.
	* Also launches the 'faucheuse' (monitor) thread 
	(if more than one philosopher exists.)
	* Initializes the start time with a small delay to synchronize threads.
	* Returns true on successful start, or prints an error message if fails.
*/
static bool	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	if (table->must_eat == 0)
	{
		printf("All philosophers have already eaten enough.\n");
		return (true);
	}
	else
	{
		table->start_time = get_time_in_ms() + (table->philo_nbr * 10);
		while (i < table->philo_nbr)
		{
			thread_operator(&table->philos[i].thread_id, philo_routine,
				&table->philos[i], THREAD_CREATE);
			i++;
		}
		if (table->philo_nbr > 1)
			thread_operator(&table->faucheuse, faucheuse, table, THREAD_CREATE);
	}
	return (true);
}

/* stop_dinner:
	* Waits for all philosopher and monitor threads to finish execution.
	* After joining threads, it destroys all mutexes and frees allocated memory.
	* Ensures a clean shutdown of the simulation without resource leaks.
*/
static void	stop_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		pthread_join(table->philos[i].thread_id, NULL);
		i++;
	}
	if (table->philo_nbr > 1)
		pthread_join(table->faucheuse, NULL);
	destroy_mutexes(table);
	free_table(table);
}

/* Main:
	* Entry point of the philosopher program.
	* Validates input arguments and formats.
	* Initializes the simulation table and data structures.
	* Launches philosopher and monitor threads.
	* Waits for completion and performs cleanup upon termination.
	* Returns EXIT_SUCCESS on normal completion, or an error code on failure.
*/
int	main(int argc, char **argv)
{
	t_table		*table;

	table = NULL;
	if (argc < 5 || argc > 6)
		return (print_msg(STR_CORRECT_ARGS, NULL, EXIT_FAILURE));
	if (!is_valid_input(argc, argv))
		return (print_msg(STR_ERR_DIGITS_ONLY, "Invalid input format",
				EXIT_FAILURE));
	table = init_table(argc, argv);
	if (!table)
		return (err_exit(STR_ERR_MALLOC, "Failed to initialise table", table));
	if (!start_dinner(table))
		return (err_exit("Failed to start dinner simulation.\n", NULL, table));
	stop_dinner(table);
	return (EXIT_SUCCESS);
}
