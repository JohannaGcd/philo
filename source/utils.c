#include "philo.h"

static void print_status(t_philo *philo, char *s)
{
    printf("%ld %d %s\n", get_time_in_ms() - philo->table->start_time, philo->philo_ID, s);
}
void write_status(t_philo *philo, bool faucheuse_info, t_status status)
{
    if (must_stop_dinner(philo->table) == true && faucheuse_info == false)
       return;
    printf("DEBUG: write_status enter id=%d\n", philo->philo_ID);
    pthread_mutex_lock(&philo->table->table_lock);
    if (status == DIED)
        print_status(philo, "died");
    else if (status == EATING)
        print_status(philo, "is eating");
    else if (status == SLEEPING)
        print_status(philo, "is sleeping"); 
    else if (status == THINKING)
        print_status(philo, "is thinking");
    else if (status == GOT_FIRST_FORK || status == GOT_SECOND_FORK)
        print_status(philo, "has taken a fork"); 
    pthread_mutex_unlock(&philo->table->table_lock);
     printf("DEBUG: write_status exit id=%d\n", philo->philo_ID);
}

void    coordinate_start(time_t start)
{
    while (get_time_in_ms() < start)
        continue ;
}

time_t get_time_in_ms(void)
{
    struct timeval time;

    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
/*void    precise_usleep(long usec, t_table *table)
{
    long start;
    long elapsed;
    long remaining;
    
    start = gettime();
    while (gettime() - start < usec)
    {
        if //simulation finished(table)
            break ;
        elapsed = gettime() - start;
        remaining = usec - elapsed;
        // spinlock threshold? what's a spinlock? why useful here?
    } 
}*/