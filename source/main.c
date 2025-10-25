#include "philo.h"

static bool start_dinner(t_table *table)
{
    int i;

    i = 0;
    /*printf("DEBUG: starting dinner: philo_nbr=%d start_time=%ld must_eat=%d\n",
       table->philo_nbr, table->start_time, table->must_eat);
    for (int i = 0; i < table->philo_nbr; ++i)
    {
        printf("DEBUG: philos[%d] addr=%p id=%d last_meal=%ld forks: one=%p two=%p\n",
            i, (void*)&table->philos[i], table->philos[i].philo_ID,
            table->philos[i].last_meal_time,
            (void*)table->philos[i].fork_one, (void*)table->philos[i].fork_two);
    }
    for (int i = 0; i < table->philo_nbr; ++i)
    printf("DEBUG: forks[%d] addr=%p mutex=%p\n", i, (void*)&table->forks[i], (void*)&table->forks[i].fork_mutex);*/
    /*printf("DEBUG: starting dinner: philo_nbr=%d start_time=%ld must_eat=%d\n",
       table->philo_nbr, table->start_time, table->must_eat);
    for (int i = 0; i < table->philo_nbr; ++i)
    {
        printf("DEBUG: philos[%d] addr=%p philo_ID=%d meals=%d last_meal=%ld fork_one=%p fork_two=%p thread_id=%p\n",
            i,
            (void*)&table->philos[i],
            table->philos[i].philo_ID,
            table->philos[i].meals_nbr,
            table->philos[i].last_meal_time,
            (void*)table->philos[i].fork_one,
            (void*)table->philos[i].fork_two,
            (void*)table->philos[i].thread_id);
    }
    for (int i = 0; i < table->philo_nbr; ++i)
        printf("DEBUG: forks[%d] addr=%p mutex=%p\n", i, (void*)&table->forks[i], (void*)&table->forks[i].fork_mutex);
    fflush(stdout);*/

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
        if (table->philo_nbr > 1)
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
    destroy_mutexes(table);
    free_table(table);
}

/* Main:
    1. Checks input 
    2. Initialises the table 
    3. Launches the routine 
    4. Stops the routine & cleans up (when philos have eaten the nbr of meals specified or if one dies)
*/
int main(int argc, char **argv)
{
    t_table *table;

    table = NULL;
    if (argc < 5 || argc > 6)
        return(print_msg(STR_CORRECT_ARGS, NULL, EXIT_FAILURE));
    if (!is_valid_input(argc, argv))
        return (print_msg(STR_ERR_DIGITS_ONLY, "Invalid input format", EXIT_FAILURE));
    table = init_table(argc, argv);
    if (!table)
        return (err_exit(STR_ERR_MALLOC, "Failed to initialise table", table));
    if (!start_dinner(table))
        return (err_exit("Failed to start dinner simulation.\n", NULL, table));
    stop_dinner(table);
    return (EXIT_SUCCESS);
}