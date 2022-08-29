/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:44:43 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/29 12:19:40 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Adds or update a variable in env linked list*/
void	export(t_cmd *cmd, t_list **env)
{
	t_list	*var;
	char	**var_key;
	int		index;

	index = 0;
	while (index++, (cmd->cmd)[index])
	{
		if (!ft_strchr((cmd->cmd)[index], '='))
			continue ;
		if (ft_strchr((cmd->cmd)[index], '=')[1] == 0)
			continue ;
		var_key = ft_split((cmd->cmd)[index], '=');
		var = ft_lstfind(*env, var_key[0]);
		clean_array((void **) var_key);
		if (var)
		{
			free(var->content);
			var->content = ft_strdup((cmd->cmd)[index]);
			continue ;
		}
		ft_lstadd_back(env, ft_lstnew(ft_strdup((cmd->cmd)[index])));
	}
}

void	unset(t_cmd *cmd, t_list **env)
{
	t_list	*var;
	char	**var_key;
	int		index;

	index = 0;
	while (index++, (cmd->cmd)[index])
	{
		var = ft_lstfind(*env, (cmd->cmd)[index]);
		if (!var)
			continue ;
		ft_lstremove(env, (cmd->cmd)[index]);
	}
}
