#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>

// macros

# define MAX_PHILO 200
# define STR_CORRECT_ARGS "warning: wrong %s arguments: ./philo <number_of_philosophers > <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define STR_PROG_NAME "philo"
# define STR_ERR_DIGITS_ONLY "%s invalid input: %s should be a positive integer between 0 and INT_MAX, ie. 2147483647.\n"
# define STR_ERR_MAX_PHILO "%s invalid input: there must be between 1 and 200 philsophers at most.\n"

// structures - philo, monitor

typedef struct  s_table t_table;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int             fork_id;
}   t_fork;

typedef struct s_philo {
    int         philo_ID;
    int         meals_nbr;
    bool        max_meals;
    long        last_meal_time;
    t_fork      *fork_left;
    t_fork      *fork_right;
    pthread_t   thread_id;
    t_table     *table;
}   t_philo;

typedef struct  s_table
{
    int     philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    int     max_meals;
    long    start;
    bool    end; // philo dies or all philos full
    t_fork  *forks;
    t_philo *philos;
}   t_table;

// function prototypes

int     warning_msg(char *str, char *detail, int exit_nbr);
bool    is_valid_input(int argc, char **argv)