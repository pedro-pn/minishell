/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:40 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/07 10:18:50 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_variables(t_data *data, char *old_cwd)
{
	t_list	*node;
	char	cwd[PATH_MAX];

	node = ft_lstfind(data->lst_env, "OLDPWD");
	free(node->content);
	node->content = ft_strjoin("OLDPWD=", old_cwd);
	getcwd(cwd, PATH_MAX);
	node = ft_lstfind(data->lst_env, "PWD");
	free(node->content);
	node->content = ft_strjoin("PWD=", cwd);
	return (0);
}

static int	move_to_oldpwd(t_data *data, char *cwd)
{
	t_list	*node;
	char	*dest;

	dest = get_value((char *)ft_lstfind(data->lst_env, "OLDPWD")->content);
	node = ft_lstfind(data->lst_env, "OLDPWD");
	free(node->content);
	node->content = ft_strjoin("OLDPWD=", cwd);
	if (!chdir(dest))
	{
		node = ft_lstfind(data->lst_env, "PWD");
		free(node->content);
		node->content = ft_strjoin("PWD=", dest);
		free(dest);
		return (0);
	}
	return (1);
}

int	__cd(char **args, t_data *data)
{
	char	cwd[PATH_MAX];
	char	*dest;

	getcwd(cwd, PATH_MAX);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		dest = getenv("HOME");
	else if (!ft_strcmp(args[1], "-"))
		return (move_to_oldpwd(data, cwd));
	else
		dest = args[1];
	if (!chdir(dest))
		return (update_pwd_variables(data, cwd));
	ft_putstr_fd(args[1], 1);
	ft_putstr_fd(": ", 1);
	perror("");
	return (1);
}
