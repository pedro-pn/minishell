/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 18:19:53 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/19 11:38:08 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*trim_spc(char *str)
{
	char	*temp;

	temp = str;
	str = ft_strtrim(temp, " ");
	free(temp);
	return (str);
}

void	clean_empty_nodes(t_list **lst)
{
	t_list	*temp;
	int		empty_nodes;

	temp = *lst;
	empty_nodes = 0;
	while (temp)
	{
		if (!ft_strcmp((char *)temp->content, ""))
			empty_nodes++;
		temp = temp->next;
	}
	while (empty_nodes > 0)
	{
		ft_lstremove_2(lst, "");
		empty_nodes--;
	}
}
