#include "philo.h"

static bool start_dinner(t_table *table)
{
    int i;

    i = 0;
    if (table->must_eat == 0) // double check if this should be done in philo_routine or if its fine here
    {
        printf("All philosophers have already eaten enough.\n"); // transform with message function
        return (true);
    }
    else
    {
        table->start_time = get_time_in_ms() + (table->philo_nbr * 20);
        while (i < table->philo_nbr)
        {
            thread_operator(&table->philos[i].thread_id, 
                philo_routine, &table->philos[i], THREAD_CREATE);
            i++;
        }
        thread_operator(&table->faucheuse, faucheuse, table, THREAD_CREATE);
    }
    return (true);
}
static void stop_dinner(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_join(table->philos[i].thread_id, NULL);
        i++;
    }
    if (table->philo_nbr > 1)
        pthread_join(table->faucheuse, NULL);
    destroy_all_mutexes(table);
    free_table(table);
}

/* Main:
    1. Checks input 
    2. Initialises the table 
    3. Launches the routine 
    4. Stops the routine & cleans up (when philos have eaten the nbr of meals specified or if one dies)
*/

// TODO: check if return exit here are a repeat from called function
int main(int argc, char **argv)
{
    t_table *table;

    table = NULL;
    if (argc < 5 || argc > 6)
        return(print_msg(STR_CORRECT_ARGS, NULL, EXIT_FAILURE));
    if (!is_valid_input(argc, argv))
        return (err_exit(STR_ERR_DIGITS_ONLY, "Invalid input format", table));
    table = init_table(argc, argv);
    if (!table)
        return (err_exit(STR_ERR_MALLOC, "Failed to initialise table", table));
    if (!start_dinner(table))
        return (err_exit("Failed to start dinner simulation.\n", NULL, table);
    stop_dinner(table); 
    return (EXIT_SUCCESS);
}