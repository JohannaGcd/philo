/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/10/27 10:46:56 by jguacide      #+#    #+#                 */
/*   Updated: 2025/10/27 14:05:12 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* int_atoi:
	Converts a digit-only string into an integer.
	Returns the number between 0 and INT MAX
	Or -1 if it exceeds INT_MAX.
*/
int	int_atoi(char *str)
{
	unsigned long long int	nbr;
	int						i;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	if (nbr > INT_MAX)
		return (-1);
	return ((int)nbr);
}

/* only_digits:
	Checks if the arguments given only contain valid digits,
	ie. Between 0 and 9, no negatives or alpha characters.
*/
static bool	only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}
/* is_valid_input:
	Checks if input is composed of digits only,
	Not negative and not bigger than INT_MAX,
	Meets number of philo requirement (between 1 and 200).
	Returns true is all args are valid, false otherwise.
*/

bool	is_valid_input(int argc, char **argv)
{
	int		i;
	int		nbr;

	i = 1;
	while (i < argc)
	{
		if (!only_digits(argv[i]))
			return (false);
		nbr = int_atoi(argv[i]);
		if (i == 1 && (nbr <= 0 || nbr > MAX_PHILO))
			return (false);
		if (i != 1 && nbr == -1)
			return (false);
		i++;
	}
	return (true);
}
