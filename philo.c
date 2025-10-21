#include "philo.h"

void    *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    write_long(&philo->meal_time_lock, philo->last_meal_time, philo->table->start_time);
    coordinate_start(philo->table->start_time);
    if (philo->table->time_to_die == 0)
        return (NULL);
    if (philo->table->philo_nbr == 1)
        return (single_philo_routine(philo)); // TODO
    else if (philo->philo_ID % 2)
        think(philo, true);
    while (did_dinner_stop(philo->table) == false)
    {
        eat_sleep(philo);
        think(philo, false);
    }
    return (NULL); 
}