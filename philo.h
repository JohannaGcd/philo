#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

// macros

# define MAX_PHILO 200
# define STR_CORRECT_ARGS "warning: wrong %s arguments: ./philo <number_of_philosophers > <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n"
# define STR_PROG_NAME "philo"
# define STR_ERR_DIGITS_ONLY "%s invalid input: %s should be a positive integer between 0 and INT_MAX, ie. 2147483647.\n"
# define STR_ERR_MAX_PHILO "%s invalid input: there must be between 1 and 200 philsophers at most.\n"
# define STR_ERR_MALLOC "Could not allocate memory at %s.\n"

// codes for mutex operations

typedef enum e_mutex_operation
{
    MUTEX_CREATE,
    MUTEX_DESTROY,
    MUTEX_LOCK,
    MUTEX_UNLOCK,
} t_mutex_operation;

typedef enum e_thread_operation 
{
    THREAD_CREATE,
    THREAD_JOIN,
} t_thread_operation;

typedef enum e_time_code 
{
    SECOND,
    MILLISECOND,
    MICROECOND,
} t_time_code;

typedef enum e_status
{
    DIED,
    EATING,
    SLEEPING,
    THINKING,
    GOT_FIRST_FORK,
    GOT_SECOND_FORK,
}   t_status;

// structures - philo, monitor

typedef struct  s_table t_table;

typedef struct s_fork
{
    pthread_mutex_t fork_mutex;
    int             fork_id;
}   t_fork;

// check if i really need longs, or if i can use ints
typedef struct s_philo {
    int         philo_ID;
    int         meals_nbr;
    int        max_meals;
    long        last_meal_time;
    t_fork      *fork_one;
    t_fork      *fork_two;
    pthread_t   thread_id;
    t_table     *table;
    pthread_mutex_t meal_time_lock;
}   t_philo;

typedef struct  s_table
{
    int     philo_nbr;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    int     must_eat;
    long    start_time;
    bool    end;
    t_fork  *forks;
    t_philo *philos;
    pthread_t   faucheuse;
    pthread_mutex_t table_lock;
}   t_table;


// function prototypes

int     print_msg(char *str, char *detail, int exit_nbr);
int    err_null(char *str, char *details, t_table *table);
void    err_exit(char *str, char *details, t_table *table);
bool    is_valid_input(int argc, char **argv);
int     int_atoi(char *str);
t_table *init_table(int argc, char **argv);
void thread_operator(pthread_t *thread, void *(*routine)(void *), void *data, t_thread_operation operation);
int mutex_operator(pthread_mutex_t *mutex, t_mutex_operation operation);
time_t get_time_in_ms(void);
void    *philo_routine(void *data);
void	write_long(pthread_mutex_t *mutex, long *dest, long value);
long	return_long(pthread_mutex_t *mutex, long *value);
void    coordinate_start(time_t start);
void write_status(t_philo *philo, bool faucheuse_info, t_status status);
void    *faucheuse(void *data);