#include "philo.h"

static bool must_stop_dinner(t_table *table)
{
    int i;
    bool all_philo_full;

    all_philo_full = true;
    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_mutex_lock(&table->philos[i].meal_time_lock);
        if (kill_philo(table->philos[i]))
        {
            pthread_mutex_unlock(&table->philos[i].meal_time_lock);
            return true;
        }
        if (table->must_eat != -1)
        {
            if (table->philos[i].meals_nbr < table->must_eat)
                all_philo_full = false;
        }
        pthread_mutex_unlock(&table->philos[i].meal_time_lock);
        i++;
    }
    if (table->must_eat != -1 && all_philo_full == true)
    {
        write_bool(&table->table_lock, table->end, true);
        return (true);
    }
    return (false);

}


void    *faucheuse(void *data)
{
    t_table *table;

    table = (t_table *)data;
    if (table->must_eat == 0)
        return (NULL);
    set_stop_flag(table, false);
    coordinate_start(table->start_time);
    while (true) // how does this work?
    {
        if (must_stop_dinner(table) == true)
            return (NULL);
        usleep(1000); // why? see if it should be replaced with custom function
    }
    return (NULL);
}