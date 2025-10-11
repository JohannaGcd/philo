# include "philo.h"

int warning_msg(char *str, char *detail, int exit_nbr)
{
    if (!detail)
        printf(str, STR_PROG_NAME);
    else
        printf(str, STR_PROG_NAME, detail);
    return (exit_nbr);
}