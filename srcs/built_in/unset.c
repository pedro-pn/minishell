/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:43:46 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/10/07 11:03:48 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__unset(char **args, t_data *data)
{
	t_list	*node;
	t_list	*empty_node;
	int		index;

	index = 0;
	while (index++, args[index])
	{
		node = ft_lstfind(data->lst_env, args[index]);
		if (!node)
			return (1);
		empty_node = ft_lstfind_2(data->empty_vars, args[index]);
		if (empty_node)
			ft_lstremove_2(&data->empty_vars, args[index]);
		if (!node)
			continue ;
		ft_lstremove(&data->lst_env, args[index]);
	}
	return (0);
}
