#include "philo.h"


// do the same for threads



// initialise a thread for each philo (and an extra one?)
// initialise as many forks as philos

static *init_threads()
{

}
static t_philo	*init_philos(t_table *table, int nbr) // or double opinteR?
{
	int i;
	t_philo **philosophers;

	i = 0;
	philosophers = malloc(sizeof(t_philo) * nbr);
	if (!philosophers)
		return (malloc_err(STR_ERR_MALLOC), "init_philos", table);
	while (i < nbr)
	{
		philosophers[i] = malloc(sizeof(t_philo) * 1);
		if (!philosophers[i])
			return (malloc_err(STR_ERR_MALLOC), "init_philos", table);
		philosophers[i]->philo_ID = i;
		philosophers[i]->meals_nbr = 0;
		philosophers[i]->max_meals = table->max_meals;
		philosophers[i]->fork_left = ;		// ???
		philosophers[i]->fork_right = ;		// ???
		philosophers[i]->thread_id = ;		// ???
		philosophers[i]->table = table;
	}
	return (philosophers);
}

long	atolong (char *str)
{
	int i;
	unsigned long nbr;

	nbr = 0;
	i = 0;
	while (str[i])
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr);
}

t_table *init_table(int argc, char **argv)
{
	int i;
	t_table *table;

	i = 1;
	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (malloc_err(STR_ERR_MALLOC, "init_table", table));
	while (argv[i])
	{
		table->philo_nbr = int_atoi(argv[i++]) * 1000;
		table->time_to_die = atolong(argv[i++]) * 1000;
		table->time_to_eat = atolong(argv[i++]) * 1000;
		table->time_to_sleep = atolong(argv[i++]) * 1000;
		table->max_meals = -1;
		if (argc == 5)
			table->max_meals = int_atoi(argv[i]);
		table->philos = init_philos(table, table->philo_nbr);
		if (!table->philos)
			return (malloc_err(STR_ERR_MALLOC, "init_table", table));
	}
	return (table);
}