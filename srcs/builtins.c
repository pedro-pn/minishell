/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:17:41 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/30 00:12:45 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_export_error(t_data *data, char *arg);
static void	ft_export_display(t_data *data);

void	__echo(char **args)
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
}

void	__cd(char **args, t_data *data)
{
	t_list	*node;
	t_list	*node_old;
	char	cwd[PATH_MAX];
	char	*new_path;
	char	*dest;
	char	*oldpwd;

	getcwd(cwd, PATH_MAX);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		dest = getenv("HOME");
	else
		dest = args[1];
	if (!chdir(dest))
	{
		node_old = ft_lstfind(data->lst_env, "OLDPWD");
		free(node_old->content);
		oldpwd = ft_strjoin("OLDPWD=", cwd);
		node_old->content = ft_strdup(oldpwd);
		free(oldpwd);

		getcwd(cwd, PATH_MAX);
		node = ft_lstfind(data->lst_env, "PWD");
		free(node->content);
		new_path = ft_strjoin("PWD=", cwd);
		node->content = ft_strdup(new_path);
		free(new_path);
		return ;
	}
	ft_putstr_fd("minishell: cd: ", 1);
	ft_putstr_fd(args[1], 1);
	ft_putstr_fd(": ", 1);
	perror("");
}

void	__pwd(char **args)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	ft_putendl_fd(cwd, 1);
}

void	__env(char **args, t_data *data)
{
	ft_lstdisplay(data->lst_env);
}


// void	validate_keyvalue(char **args)
// {
// 	int	i;
	
// 	i = 0;
// 	while (args[i])
// 		i++;
// 	if (i == 1)
// 		return ;
// 	i = 0;
// 	if (ft_strchr(*args++, ' '))
// 	{
// 		raise_error("'=", 2);
// 		exit(1);
// 	}
// 	if (ft_strchr(*args++, ' '))
// 	{
// 		raise_error("='", 2);
// 		exit(1);
// 	}
// }
char	*get_keyvalue(char *arg)
{
	char	*ptr_key;
	char	*trimmed_key;
	char	*ptr_value;
	char	*value;
	char	*key;
	char	*key_value;


	ptr_key = get_key(arg);
	trimmed_key = ft_strtrim(ptr_key, " ");
	free(ptr_key);
	ptr_value = get_value(arg);
	value = ft_strtrim(ptr_value, " ");
	free(ptr_value);
	key = ft_strjoin(trimmed_key, "=");
	free(trimmed_key);
	key_value = ft_strjoin(key, value);
	free(key);
	free(value);
	return (key_value);
}

/* Adds or update a variable in env linked list*/
void	__export(char **args, t_data *data)
{
	t_list	*var;
	char	**var_key;
	int		index;

	index = 0;
	if (args[1] == NULL)
		ft_export_display(data);
	while (index++, args[index])
	{
		if (check_export_error(data, args[index]))
			continue ;
		var_key = ft_split(args[index], '=');
		var = ft_lstfind(data->lst_env, var_key[0]);
		if (ft_lstfind_2(data->empty_vars, var_key[0]))
			ft_lstremove_2(&data->empty_vars, var_key[0]);
		clean_array((void **) var_key);
		if (var)
		{
			free(var->content);
			var->content = ft_strdup(args[index]);
			continue ;
		}
		ft_lstadd_back(&data->lst_env, ft_lstnew(ft_strdup(args[index])));
	}
}

/* Removes environment variables from a linked list*/
void	__unset(char **args, t_data *data)
{
	t_list	*node;
	t_list	*empty_node;
	int		index;

	index = 0;
	while (index++, args[index])
	{
		node = ft_lstfind(data->lst_env, args[index]);
		empty_node = ft_lstfind_2(data->empty_vars, args[index]);
		if (empty_node)
			ft_lstremove_2(&data->empty_vars, args[index]);
		if (!node)
			continue ;
		ft_lstremove(&data->lst_env, args[index]);
	}
}

static int	check_export_error(t_data *data, char *arg)
{
	if (!ft_strchr(arg, '='))
	{
		if (!ft_lstfind_2(data->empty_vars, arg) 
			&& !ft_lstfind(data->lst_env, arg))
			ft_lstadd_back(&data->empty_vars, ft_lstnew(ft_strdup(arg)));
		return (1);
	}
	if (arg[0] == '=')
	{
		ft_printf("minishell: export: '%s': not a valid identifier\n", arg);
		return (1);
	}
	return (0);
}

static void	ft_export_display(t_data *data)
{
	t_list	*export_env;
	t_list	*temp;

	if (!data->lst_env)
		return ;
	export_env = ft_lstmap(data->lst_env, get_declared_vars, free);
	ft_lstdisplay(export_env);
	temp = data->empty_vars;
	while (temp)
	{
		ft_printf("declare -x %s\n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&export_env, free);
}
