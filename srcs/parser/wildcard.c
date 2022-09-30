/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:45:06 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/30 08:03:15 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_wildcard(t_list **args);
void	add_wildcard(t_wild *info, t_list **args, struct dirent *dirp);
int		search_pattern(char *file, t_wild info);
int		match_pattern(char **arg, char **file);

void	expand_wildcard(t_list **args)
{
	if (ft_strchr((char *)(*args)->content, '*'))
		get_wildcard(args);
}

void	get_wildcard(t_list **args)
{
	DIR				*dp;
	struct dirent	*dirp;
	t_wild			info;

	info.flag = 0;
	info.arg = ft_strdup((char *)(*args)->content);
	dp = opendir(ft_lstfind_value(g_data.lst_env, "PWD"));
	dirp = readdir(dp);
	while (dirp)
	{
		add_wildcard(&info, args, dirp);
		dirp = readdir(dp);
	}
	free(info.arg);
	closedir(dp);
}

void	add_wildcard(t_wild *info, t_list **args, struct dirent *dirp)
{
	if (dirp->d_name[0] == '.')
		return ;
	if (search_pattern(dirp->d_name, *info))
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

int	search_pattern(char *file, t_wild info)
{
	while (*(info.arg))
	{
		if (*(info.arg) == '*')
		{
			while (*(info.arg) == '*')
				info.arg++;
			if (!(*info.arg))
				return (1);
			while ((*(info.arg) != *file) && *file)
				file++;
			if (!*file)
				return (0);
		}
		if (!match_pattern(&(info.arg), &file))
			return (0);
	}
	if (!*file)
		return (1);
	return (0);
}

int	match_pattern(char **arg, char **file)
{
	if (**arg != **file)
		return (0);
	(*arg)++;
	(*file)++;
	if (!(**arg) && **file)
	{
		while (**arg != '*')
			(*arg)--;
	}
	else if ((**arg != **file) && **file && **arg != '*')
	{
		(*arg)--;
		while ((**arg != **file) && **file)
			(*file)++;
	}
	return (1);
}
