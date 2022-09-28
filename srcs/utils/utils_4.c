/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 05:31:14 by coder             #+#    #+#             */
/*   Updated: 2022/09/28 05:49:43 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	throw_pipe_error(int err, t_data *data)
{
	if (err == 1)
		ft_putendl_fd(ERR_PIPE1, 2);
	else if (err == 2)
		ft_putendl_fd(ERR_PIPE2, 2);
	data->invalid_syntax = 1;
	data->status = 2;
}
