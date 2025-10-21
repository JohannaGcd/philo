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
    if (argc - 1 < 4 || argc - 1 < 5)
        return(warning_msg(STR_CORRECT_ARGS, NULL, EXIT_FAILURE));
    if (!is_valid_input(argc, argv))
        return (EXIT_FAILURE);
    table = init_table(argc, argv);
    if (!table)
        return (EXIT_FAILURE);
    if (!start_dinner(table))
        return (EXIT_FAILURE);
    stop_dinner(table);
    return (EXIT_SUCCESS);

}