#include "philo.h"

// summarize each function
// create makefile
// create tester

static void assign_forks(t_philo *philo)
{	
	int id;
	int total;

	id = philo->philo_ID;
	total = philo->table->philo_nbr;
	if (id % 2 == 0)
	{
		// even philo: right then left
		philo->fork_one = id;
		philo->fork_two = (id + 1) % total;	
	}
	else
	{
		// odd philo: left then right
		philo->fork_one = id;
		philo->fork_two = (id + 1) % total;
	}
}

t_fork *init_forks(t_table *table, int nbr, t_philo *philos)
{
	int i;

	i = 0;
	t_fork *forks;
	forks = malloc(sizeof(t_fork) * nbr);
	if (!forks)
		return (malloc_err(STR_ERR_MALLOC), "init_forks", table); // make sure this exits or returns correctly with freeing,
	while (i < nbr)
	{
		forks[i].fork_id = i;
		mutex_operator(&forks[i].fork_mutex, MUTEX_CREATE);
		i++;
	}
	return (forks);
}
t_philo	*init_philos(t_table *table, int nbr)
{
	int i;
	t_philo *philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * nbr);
	if (!philos)
		return (malloc_err(STR_ERR_MALLOC), "init_philos", table); // check safe return with freeing, or exit?
	while (i < nbr)
	{
		philos[i].philo_ID = i + 1;
		philos[i].meals_nbr = 0;
		philos[i].max_meals = table->must_eat;
		assign_forks(&philos[i]);
		philos[i].table = table;
		i++;
	}
	return (philos);
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
	while (argv[i]) // check incrementation
	{
		table->philo_nbr = int_atoi(argv[i++]);
		table->time_to_die = atolong(argv[i++]) * 1000;
		table->time_to_eat = atolong(argv[i++]) * 1000;
		table->time_to_sleep = atolong(argv[i++]) * 1000;
		table->must_eat = -1;
		if (argc == 5)
			table->must_eat = int_atoi(argv[i]);
		table->philos = init_philos(table, table->philo_nbr);
		if (!table->philos)
			return (malloc_err(STR_ERR_MALLOC, "init_table", table));
		table->forks = init_forks(table, table->philo_nbr, table->philos);
		if (!table->forks)
			return (malloc_err(STR_ERR_MALLOC, "init_forks", table));
	}
	return (table);
}