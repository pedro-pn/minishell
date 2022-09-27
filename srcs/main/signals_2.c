/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:14:14 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/22 11:14:24 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_signals(t_data *data, int status, int process, int processes_n)
{
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		data->status = 130;
	}
	if (WTERMSIG(status) == SIGQUIT && process == processes_n - 1)
	{
		write(1, "Quit\n", 5);
		data->status = 131;
	}
	return (data->status);
}
