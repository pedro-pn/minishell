/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:42:53 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/06 17:01:09 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	__pwd(char **args)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	ft_putendl_fd(cwd, 1);
	return (0);
}
