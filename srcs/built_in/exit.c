/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 16:53:39 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/04 17:13:27 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	__exit(char **cmds, t_data *data)
{
	unsigned int	status_code;

	if (cmds[1])
	{
		status_code = ft_atoi(cmds[1]);
		exit(status_code);
	}
	exit(data->status);
}
