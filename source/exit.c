# include "philo.h"

void    destroy_mutexes(t_table *table)
{
    int i;

    i = 0;
    while (i < table->philo_nbr)
    {
        pthread_mutex_destroy(&table->forks[i].fork_mutex);
        pthread_mutex_destroy(&table->philos[i].meal_time_lock);
        i++;
    }
    pthread_mutex_destroy(&table->table_lock);
}

void    *free_table(t_table *table)
{
    if (!table)
        return (NULL);
    if (table->forks)
        free(table->forks);
    if (table->philos)
        free(table->philos);
    free(table);
    return (NULL);
}

int print_msg(char *str, char *detail, int exit_nbr)
{
    if (!detail)
        printf(str, STR_PROG_NAME);
    else
        printf(str, STR_PROG_NAME, detail);
    return (exit_nbr);
}

void    *err_null(char *str, char *details, t_table *table)
{
    if (table != NULL)
        free_table(NULL);
    print_msg(str, details, EXIT_FAILURE);
    return (NULL);
}

int    err_exit(char *str, char *details, t_table *table)
{
    if (table != NULL)
        free_table(table);
    return (print_msg(str, details, EXIT_FAILURE));
}