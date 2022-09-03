/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:53:05 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/02 09:37:53 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_path(t_data *data, char **cmd, char **path)
{
	char	**bin_paths;
	t_list	*path_node;
	int		status;
	
	if (!*cmd)
		return (1);
	if (ft_strchr(*cmd, '/'))
		status = get_given_path(data, cmd, path);
	if (!status)
		return (status);
	path_node = ft_lstfind(data->lst_env, "PATH");
	bin_paths = ft_split((char *)path_node->content, ':');
	status = check_path(bin_paths, *cmd, path);
	clean_array((void **)bin_paths);
	return (status);
}

int	get_given_path(t_data *data, char **cmd, char **path)
{
	char	*name;

	if (access(*cmd, F_OK))
		return (1);
	name = ft_strdup(ft_strrchr(*cmd, '/') + 1);
	*path = *cmd;
	*cmd = name;
	return (0);
}

int	check_path(char **bin_paths, char *cmd, char **path)
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