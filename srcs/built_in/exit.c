/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:53:39 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/05 12:22:55 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_exit_code(char *nptr);
static int	arg_count(char **args);

int	__exit(char **cmds, t_data *data)
{
	unsigned int	status_code;

	if (cmds[1])
	{
		status_code = ft_atoi(cmds[1]);
		if (check_exit_code(cmds[1]))
		{
			if (arg_count(cmds) > 2)
			{
				ft_putendl_fd("bash: exit: too many arguments", 2);
				return (1);
			}
			clean_executor();
			exit(status_code);
		}
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmds[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		clean_executor();
		exit(2);
	}
	clean_executor();
	exit(data->status);
}

static int	check_exit_code(char *nptr)
{
	while ((*nptr) && (*nptr == '\n' || *nptr == '\t'
			|| *nptr == '\r' || *nptr == '\f'
			|| *nptr == '\v' || *nptr == 32))
		++nptr;
	if (*nptr == '+' || *nptr == '-')
		++nptr;
	while (*nptr)
	{
		if (!ft_isdigit(*nptr))
			return (0);
		++nptr;
	}
	return (1);
}

static int	arg_count(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}
