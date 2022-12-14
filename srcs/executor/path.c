/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:53:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/10/05 14:45:49 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_given_path(char **cmd, char **path);
static int	check_path(char **bin_paths, char *cmd, char **path);

void	get_path(t_data *data, char **cmd, char **path)
{
	char	**bin_paths;
	char	*path_value;
	int		status;

	status = 1;
	if (!cmd)
		return ;
	if (ft_strchr(*cmd, '/'))
		status = get_given_path(cmd, path);
	if (!status)
		return ;
	path_value = ft_lstfind_value(data->lst_env, "PATH");
	if (!path_value)
		return ;
	bin_paths = ft_split(path_value, ':');
	status = check_path(bin_paths, *cmd, path);
	clean_array((void **)bin_paths);
}

static int	get_given_path(char **cmd, char **path)
{
	char		*name;
	struct stat	path_stat;

	path_stat.st_mode = 0;
	stat(*cmd, &path_stat);
	if (access(*cmd, F_OK))
		return (1);
	name = ft_strdup(ft_strrchr(*cmd, '/') + 1);
	if (!S_ISDIR(path_stat.st_mode))
	{
		*path = *cmd;
		*cmd = name;
	}
	else
		free(name);
	return (0);
}

static int	check_path(char **bin_paths, char *cmd, char **path)
{
	int		index;
	char	*path_test;
	char	*temp;
	int		status;

	index = -1;
	while (index++, bin_paths[index])
	{
		temp = ft_strjoin(bin_paths[index], "/");
		path_test = ft_strjoin(temp, cmd);
		free(temp);
		if (access(path_test, F_OK) == 0)
		{
			status = 0;
			break ;
		}
		else
			status = 1;
		free(path_test);
		path_test = NULL;
	}
	*path = path_test;
	return (status);
}
