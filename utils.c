#include "philo.h"

//(get time) to continue

time_t get_time_in_ms(void)
{
    struct timeval time;

    if (gettimeofday(&time, NULL) != 0)
        exit ; //write exit error
    return ((time.tv_sec * 1000) + (time.tv_sec / 1000));
}
void    precise_usleep(long usec, t_table *table)
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
}

// print status: uses a lock to write the status, with philo id and action
// how does mc handle safe_mutex_handle?
// implement waiting on threads  (spnilock?)
// then print status and safe mutex handle
// then usleep 
// then eat
// then think
// function to monitor / grim, so checking if all threads are running 