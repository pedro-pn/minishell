/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:40:56 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/03 10:49:28 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__echo(char **args, t_data *data)
{
	int	flag;
	int	i;

	i = 1;
	if (!args[i])
	{
		ft_putstr_fd("\n", 1);
		return ;
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
	// g_status = 0;
}
