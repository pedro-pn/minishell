/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d < ppaulo-d@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:17:38 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/13 19:50:27 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_valid_identifier(char *arg)
{
	int		index;

	index = -1;
	while (index++, arg[index] != '=' && arg[index])
	{
		if (!ft_isalnum(arg[index]))
		{
			if (arg[index] == '_')
				continue ;
			if (arg[index] == '+' && arg[index + 1] == '=')
				continue ;
			return (1);
		}
	}
	return (0);
}

static int	check_export_error(t_data *data, char *arg)
{
	if (ft_isdigit(arg[0]) || arg[0] == '=' || check_valid_identifier(arg))
	{
		ft_printf("minishell: export: '%s': not a valid identifier\n", arg);
		g_status = 1;
		return (1);
	}
	if (!ft_strchr(arg, '='))
	{
		if (!ft_lstfind_2(data->empty_vars, arg) 
			&& !ft_lstfind(data->lst_env, arg))
			ft_lstadd_back(&data->empty_vars, ft_lstnew(ft_strdup(arg)));
		return (1);
	}
	return (0);
}

static int	ft_export_display(t_data *data)
{
	t_list	*export_env;
	t_list	*temp;

	if (!data->lst_env)
		return (1);
	export_env = ft_lstmap(data->lst_env, get_declared_vars, free);
	ft_lstdisplay(export_env);
	temp = data->empty_vars;
	while (temp)
	{
		ft_printf("declare -x %s\n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&export_env, free);
	return (0);
}

void	update_variable(t_data *data, char *arg, char *var)
{
	t_list	*var_node;

	var_node = ft_lstfind(data->lst_env, var);
	if (var_node)
	{
		free(var_node->content);
		var_node->content = ft_strdup(arg);
		return ;
	}
	ft_lstadd_back(&data->lst_env, ft_lstnew(ft_strdup(arg)));
}

void	append_variable(t_data *data, char *arg, char *var)
{
	t_list	*var_node;
	char	*temp;

	*ft_strchr(var, '+') = 0;
	var_node = ft_lstfind(data->lst_env, var);
	if (var_node)
	{
		temp = (char *) var_node->content;
		var_node->content = ft_strjoin(temp, ft_strchr(arg, '+') + 2);
		free(temp);
		return ;
	}
	temp = ft_strjoin(var, "=");
	ft_lstadd_back(&data->lst_env, ft_lstnew(ft_strjoin(temp,
				ft_strchr(arg, '=') + 1)));
	free(temp);
}

int	check_for_append(char *var)
{
	char	*key;
	
	key = ft_strchr(var, '+');
	if (!key)
		return (0);
	if (*(++key) == 0)
		return (1);
	return (0);
}

int	__export(char **args, t_data *data)
{
	char	**var_key;
	int		index;

	index = 0;
	g_status = 0;
	if (args[1] == NULL)
		return (ft_export_display(data));
	while (index++, args[index])
	{
		if (check_export_error(data, args[index]))
			continue ;
		var_key = ft_split(args[index], '=');
		if (ft_lstfind_2(data->empty_vars, var_key[0]))
			ft_lstremove_2(&data->empty_vars, var_key[0]);
		if (check_for_append(var_key[0]))
			append_variable(data, args[index], var_key[0]);
		else
			update_variable(data, args[index], var_key[0]);
		clean_array((void **) var_key);
	}
	return (0);
}
