# include "philo.h"

void    *free_table(t_table *table)
{
    int i;
    
    if (!table)
        return (NULL);
    // free locks
    // free philos
    free(table);
    return (NULL);
}

int warning_msg(char *str, char *detail, int exit_nbr)
{
    if (!detail)
        printf(str, STR_PROG_NAME);
    else
        printf(str, STR_PROG_NAME, detail);
    return (exit_nbr);
}

void    malloc_err(char *str, char *details, t_table *table)
{
    if (table != NULL)
        free_table(NULL);
    warning_msg(str, details, EXIT_FAILURE);
    return (NULL);
}