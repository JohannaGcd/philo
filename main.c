#include "philo.h"

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
    table = init_table(argc, argv, 1);
    if (!table)
        return (EXIT_FAILURE);
    if (!start_dinner(table))
        return (EXIT_FAILURE);
    stop_dinner(table);
    return (EXIT_SUCCESS);

}