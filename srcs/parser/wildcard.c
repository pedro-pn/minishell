/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:45:06 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/29 13:15:29 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_wildcard(t_list **args);
void	add_wildcard(t_wild *info, t_list **args, struct dirent *dirp);
int		new_wildcard(char *file, t_wild info);

void	expand_wildcard(t_list **args)
{
	if (ft_strchr((char *)(*args)->content, '*'))
		get_wildcard(args);
}

void	get_wildcard(t_list **args)
{
	DIR 			*dp;
	struct dirent	*dirp;
	t_wild			info;

	info.flag = 0;
	info.arg = ft_strdup((char *)(*args)->content);
	dp = opendir(ft_lstfind_value(g_data.lst_env, "PWD"));
	while((dirp = readdir(dp)))
		add_wildcard(&info, args, dirp);
	free(info.arg);
	closedir(dp);
}

void	add_wildcard(t_wild *info, t_list **args, struct dirent *dirp)
{
	if (dirp->d_name[0] == '.')
		return ;
	if (new_wildcard(dirp->d_name, *info))
	{
		if (!info->flag)
		{
			free((*args)->content);
			(*args)->content = ft_strdup(dirp->d_name);
			info->flag++;
		}
		else
			ft_lstadd_front(args, ft_lstnew(ft_strdup(dirp->d_name)));
	}
}

int	new_wildcard(char *file, t_wild info)
{
	int	index;

	index = 0;
	while (*(info.arg))
	{
		if (*(info.arg) == '*')
		{
			info.arg++;
			if (!(*info.arg))
				return (1);
			while ((*(info.arg) != file[index]) && file[index])
				index++;
			if (!file[index])
				return (0);
		}
		if (*(info.arg) == file[index])
		{
			info.arg++;
			index++;
			if (!*(info.arg) && file[index])
			{
				while (*(info.arg) != '*')
					info.arg--;
			}
		}
		else
			return (0) ;
	}
	if (!file[index])
		return (1);
	return (0);
}