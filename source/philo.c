#include "philo.h"

static void philo_eat_then_sleep(t_philo *philo)
{
    pthread_mutex_lock(&philo->fork_one->fork_mutex);
    write_status(philo, false, GOT_FIRST_FORK);
    pthread_mutex_lock(&philo->fork_two->fork_mutex);
    write_status(philo, false, GOT_SECOND_FORK);
    write_status(philo, false, EATING);
    write_long(&philo->meal_time_lock, &philo->last_meal_time, get_time_in_ms());
    philo_sleep(philo->table, philo->table->time_to_eat); // check Oversion
    pthread_mutex_unlock(&philo->fork_one->fork_mutex);
    pthread_mutex_unlock(&philo->fork_two->fork_mutex);
}
void    philo_sleep(t_table *table, time_t time_to_sleep)
{
    time_t wake_up;

    wake_up = get_time_in_ms() + time_to_sleep;
    while (get_time_in_ms() < wake_up)
    {
        if (has_dinner_stopped(table))
            break;
       usleep(100);
    }
}

static void *single_philo(t_philo *philo)
{
     printf("DEBUG: single_philo start: philo=%p id=%d fork_one=%p fork_two=%p\n",
           (void*)philo, philo->philo_ID, (void*)philo->fork_one, (void*)philo->fork_two);
    if (!philo->fork_one) {
        fprintf(stderr, "BUG: single_philo: fork_one is NULL\n");
        return NULL;
    }
    pthread_mutex_lock(&philo->fork_one->fork_mutex);
    printf("DEBUG: locked fork_one for id=%d\n", philo->philo_ID);
    write_status(philo, false, GOT_FIRST_FORK);
    printf("DEBUG: after write_status(GOT_FIRST_FORK) id=%d\n", philo->philo_ID);

    philo_sleep(philo->table, philo->table->time_to_die);
    printf("DEBUG: after philo_sleep for id=%d\n", philo->philo_ID);
    write_status(philo, false, DIED);
    printf("DEBUG: after write_status(DIED) id=%d\n", philo->philo_ID);
    pthread_mutex_unlock(&philo->fork_two->fork_mutex);
    printf("DEBUG: after unlock fork_one id=%d -- returning\n", philo->philo_ID);
    return (NULL);
}

static void philo_think(t_philo *philo, bool delay)
{
    time_t thinking_time;

    pthread_mutex_lock(&philo->meal_time_lock);
    thinking_time = (philo->table->time_to_die - (get_time_in_ms() - philo->last_meal_time) - philo->table->time_to_eat) / 2;
    pthread_mutex_unlock(&philo->meal_time_lock);
    if (thinking_time < 0)
        thinking_time = 0;
    if (thinking_time == 0 && delay == true)
        thinking_time = 1;
    if (thinking_time > 600)
        thinking_time = 200;
    if (delay == false)
        write_status(philo, false, THINKING);
    philo_sleep(philo->table, thinking_time);
}

void    *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    write_long(&philo->meal_time_lock, &philo->last_meal_time, philo->table->start_time);
    coordinate_start(philo->table->start_time);
    if (philo->table->time_to_die == 0)
        return (NULL);
    if (philo->table->philo_nbr == 1)
        return (single_philo(philo));
    else if (philo->philo_ID % 2)
        philo_think(philo, true);
    while (has_dinner_stopped(philo->table) == false)
    {
        philo_eat_then_sleep(philo);
        philo_think(philo, false);
    }
    return (NULL); 
}