/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:40:56 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/06 17:00:52 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__echo(char **args, t_data *data)
{
	int	flag;
	int	i;

	i = 1;
	if (!args[i])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	flag = 1;
	if (!ft_strncmp(args[i], "-n", 3))
	{
		flag = 0;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
