#include "philo.h"

static void	assign_forks(t_philo *philo)
{
	int	id;
	int	total;

	id = philo->philo_ID - 1;
	total = philo->table->philo_nbr;
	if (id % 2 == 0)
	{
		philo->fork_one = &philo->table->forks[id];
		philo->fork_two = &philo->table->forks[(id + 1) % total];
	}
	else
	{
		philo->fork_one = &philo->table->forks[(id + 1) % total];
		philo->fork_two = &philo->table->forks[id];
	}
}

static t_fork	*init_forks(t_table *table, int nbr)
{
	int		i;
	t_fork	*forks;

	i = 0;
	forks = malloc(sizeof(t_fork) * nbr);
	if (!forks)
		return (err_null(STR_ERR_MALLOC, "init_forks", table));
	while (i < nbr)
	{
		forks[i].fork_id = i;
		mutex_operator(&forks[i].fork_mutex, MUTEX_CREATE);
		i++;
	}
	table->forks = forks;
	i = 0;
	while (i < nbr)
	{
		assign_forks(&table->philos[i]);
		i++;
	}
	return (forks);
}
static t_philo	*init_philos(t_table *table, int nbr)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * nbr);
	if (!philos)
		return (err_null(STR_ERR_MALLOC, "init_philos", table));
	while (i < nbr)
	{
		philos[i].philo_ID = i + 1;
		philos[i].meals_nbr = 0;
		philos[i].max_meals = table->must_eat;
		philos[i].table = table;
		mutex_operator(&philos[i].meal_time_lock, MUTEX_CREATE);
		i++;
	}
	return (philos);
}

static long	atolong(char *str)
{
	int				i;
	unsigned long	nbr;

	nbr = 0;
	i = 0;
	while (str[i])
	{
		nbr = (nbr * 10) + (str[i] - '0');
		i++;
	}
	return (nbr);
}

t_table	*init_table(int argc, char **argv)
{
	int 		i;
	t_table 	*table;

	i = 1;
	table = malloc(sizeof(t_table) * 1);
	if (!table)
		return (err_null(STR_ERR_MALLOC, "init_table", table));
	table->philo_nbr = int_atoi(argv[i++]);
	table->time_to_die = atolong(argv[i++]);
	table->time_to_eat = atolong(argv[i++]);
	table->time_to_sleep = atolong(argv[i++]);
	table->must_eat = -1;
	if (argc == 6)
		table->must_eat = int_atoi(argv[i]);
	table->end = false;
	pthread_mutex_init(&table->table_lock, NULL);
	table->philos = init_philos(table, table->philo_nbr);
	if (!table->philos)
		return (err_null(STR_ERR_MALLOC, "init_table: philos", table));
	table->forks = init_forks(table, table->philo_nbr);
	if (!table->forks)
		return (err_null(STR_ERR_MALLOC, "init_table: forks", table));
	return (table);
}