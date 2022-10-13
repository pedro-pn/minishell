/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 15:05:40 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/10/13 19:37:26 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd_variables(t_data *data, char *old_cwd);
static int	move_to_oldpwd(t_data *data, char *cwd);
static void	check_for_pwd(t_data *data, char *old_cwd);

static void	check_for_pwd(t_data *data, char *old_cwd)
{
	char	*pwd;

	if (ft_lstfind(data->lst_env, "PWD"))
		return ;
	pwd = ft_strjoin("PWD=", old_cwd);
	ft_lstadd_back(&data->lst_env, ft_lstnew(pwd));
}

static int	update_pwd_variables(t_data *data, char *old_cwd)
{
	t_list	*node;
	char	cwd[PATH_MAX];

	check_for_pwd(data, old_cwd);
	node = ft_lstfind(data->lst_env, "OLDPWD");
	if (!node)
		return (1);
	free(node->content);
	node->content = ft_strjoin("OLDPWD=", old_cwd);
	getcwd(cwd, PATH_MAX);
	node = ft_lstfind(data->lst_env, "PWD");
	if (!node)
		return (1);
	free(node->content);
	node->content = ft_strjoin("PWD=", cwd);
	return (0);
}

static int	move_to_oldpwd(t_data *data, char *cwd)
{
	t_list	*node;
	char	*dest;

	node = ft_lstfind(data->lst_env, "OLDPWD");
	if (!node)
	{
		ft_putendl_fd("-minishell: cd: OLDPWD not set", 2);
		return (1);
	}
	dest = get_value((char *)node->content);
	free(node->content);
	node->content = ft_strjoin("OLDPWD=", cwd);
	if (!chdir(dest))
	{
		node = ft_lstfind(data->lst_env, "PWD");
		if (!node)
			return (1);
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
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("-minishell: cd: too many arguments\n", 2);
		return (1);
	}
	getcwd(cwd, PATH_MAX);
	if (!args[1] || !ft_strcmp(args[1], "~"))
		dest = getenv("HOME");
	else if (!ft_strcmp(args[1], "-"))
		return (move_to_oldpwd(data, cwd));
	else
		dest = args[1];
	if (!chdir(dest))
		return (update_pwd_variables(data, cwd));
	ft_putstr_fd(args[1], 2);
	perror(": ");
	return (1);
}
