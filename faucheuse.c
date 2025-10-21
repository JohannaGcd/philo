#include "philo.h"

static bool must_stop_dinner(t_table *table)
{
    int i;
    bool philo_all_full;
    t_philo *philo;

    philo_all_full = true;
    philo = table->philos;
    i = 0;
    while (i < table->philo_nbr)
    {
        write_long(&philo[i].meal_time_lock, philo[i].last_meal_time, philo[i]->//which value should i passs? am i reading or writing?);
    }// continue
    if (table->must_eat != -1 && philo_all_full == true)
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