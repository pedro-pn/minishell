/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:00:01 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/27 14:34:39 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_minishell(t_data *data)
{
	clean_data(data);
	rl_clear_history();
	ft_lstclear(&data->lst_env, free);
	ft_putendl_fd("exit", 1);
	exit(data->status);
}

void	parse_and_execute(t_data *data)
{
	check_open_var(data->prompt.line);
	if (data->invalid_syntax)
	{
		ft_putendl_fd("Invalid syntax", 2);
		return ;
	}
	expansions(data->lst_env, &data->prompt.line);
	data->exec_data = parser_input(data, data->prompt.line);
	data->status = executor(data);
}
