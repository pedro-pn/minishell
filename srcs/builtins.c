/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 23:17:41 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/08/29 13:05:04 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	__export(char **args, t_data *data)
{
	t_list	*node;
	char	*key_value;
	char	*arg;
	char	*key;
	char	*value;

	// validate_keyvalue(args + 1);
	if (!ft_strchr(args[1], '='))   // export -x foo
		return ;                    
	key = get_key(args[1]);
	value = ft_strchr(args[1], '=') + 1; // export -x foo=""
	if (!*value)
	{
		node = ft_lstfind(data->lst_env, key);
		if (!node)
			ft_lstadd_back(&data->lst_env, ft_lstnew(ft_strdup(args[1])));
		else
		{
			free(node->content);
			node->content = ft_strdup(args[1]);
		}
		free(key);
		return ;
	}
	node = ft_lstfind(data->lst_env, key);
	if (!node)
	{
		key_value = get_keyvalue(args[1]);
		ft_lstadd_back(&data->lst_env, ft_lstnew(ft_strdup(key_value)));
		free(key_value);
		return ;
	}
	node = ft_lstfind(data->lst_env, key);
	free(node->content);
	key_value = get_keyvalue(args[1]);
	node->content = ft_strdup(key_value);
	free(key_value);
}

void	__unset(char **args, t_data *data)
{
	t_list	*node;
	int		index;

	index = 0;
	while (index++, args[index])
	{
		node = ft_lstfind(data->lst_env, args[index]);
		if (!node)
			continue ;
		ft_lstremove(&data->lst_env, args[index]);
	}
}
