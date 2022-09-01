/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 05:40:56 by frosa-ma          #+#    #+#             */
/*   Updated: 2022/09/01 13:38:43 by frosa-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand(char **args, int i, int flag, t_data *data);
static int	put_echo_args(char **args, int i, t_data *data);

void	__echo(char **args, t_data *data)
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
		i = put_echo_args(args, i, data);
	if (flag)
		ft_putstr_fd("\n", 1);
	// g_status = 0;
}

static int	expand(char **args, int i, int flag, t_data *data)
{
	t_list	*node;
	char 	*var;
	
	if (flag) // echo $?
	{
		ft_putnbr_fd(42, 1);  // printar o valor de saida do ultimo comando da pipeline
		ft_putstr_fd(" ", 1);
	}
	else
	{
		node = ft_lstfind(data->lst_env, ft_strchr(args[i], '$') + 1);
		if (!node)
			return (++i);
		var = get_value((char *)node->content);
		ft_putstr_fd(var, 1);
		free(var);
		ft_putstr_fd(" ", 1);
	}
	return (++i);
}

static int	put_echo_args(char **args, int i, t_data *data)
{
	if (!ft_strcmp(args[i], "$?"))
		return (expand(args, i, 1, data));
	if (args[i][0] == '$')
		return (expand(args, i, 0, data));
	ft_putstr_fd(args[i], 1);
	if (args[i + 1])
		ft_putstr_fd(" ", 1);
	return (++i);
}
