/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:45:06 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/26 17:50:43 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_wildcard(t_list **args);
void	check_wildcard_value(char *arg, char *file, t_wild *info);
int	post_wild(t_wild info, char *file);
int	pre_wild(t_wild info, char *file);
int	search_wildcard(char *arg, char *file, t_wild info);
int	ft_strrncmp(const char *s1, const char *s2, size_t n);

void	expand_wildcard(t_list **args)
{
	t_list	*line_lst;
	
	if (ft_strchr((char *)(*args)->content, '*'))
		get_wildcard(args);
}

void	get_wildcard(t_list **args)
{
	DIR 			*dp;
	struct dirent	*dirp;
	t_wild			info;
	int				flag;

	flag = 0;
	info.arg = ft_strdup((char *)(*args)->content);
	dp = opendir(ft_lstfind_value(data.lst_env, "PWD"));
	while(dirp = readdir(dp))
	{
		check_wildcard_value(info.arg, dirp->d_name, &info);
		if (search_wildcard(info.arg, dirp->d_name, info))
		{
			if (!flag)
			{
				free((*args)->content);
				(*args)->content = ft_strdup(dirp->d_name);
				flag++;
			}
			else
				ft_lstadd_front(args, ft_lstnew(ft_strdup(dirp->d_name)));
		}
		free(info.pre_wild);
	}
	free(info.arg);
	closedir(dp);
}

void	check_wildcard_value(char *arg, char *file, t_wild *info)
{
	int	index;
	
	info->arg_len = ft_strlen(arg);
	info->file_len = ft_strlen(file);
	info->post_Wild = ft_strchr(arg, '*') + 1;
	info->pre_wild = ft_substr(arg, 0, info->arg_len - 1);
	index = 0;
	while (arg[index])
	{
		if (arg[index] == '*')
		{
			info->wild_index = index;
			break ;
		}
		index++;
	}
}


int	post_wild(t_wild info, char *file)
{
	if (!ft_strrncmp(file, info.post_Wild, ft_strlen(info.post_Wild)))
		return (1);
	return (0);
}

int	pre_wild(t_wild info, char *file)
{
	if (!ft_strncmp(file, info.pre_wild, info.wild_index))
		return (1);
	return (0);
}

int	search_wildcard(char *arg, char *file, t_wild info)
{

	if (info.wild_index == 0)
		return (post_wild(info, file));
	else if (info.wild_index == info.arg_len - 1) // for "abc*" case
		return (pre_wild(info, file));
	else if (post_wild(info, file) && pre_wild(info, file))
		return (1);
	return (0);
}
