/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:28:23 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/12 12:01:32 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_quotes(char **array)
{
	int	index;

	index = 0;
	while(array[index])
	{
		ft_memrpl(array[index], CTRL_SPC, 32, ft_strlen(array[index]));
		ft_memrpl(array[index], CTRL_D, 34, ft_strlen(array[index]));
		ft_memrpl(array[index], CTRL_S, 39, ft_strlen(array[index]));
		index++;
	}
}

void	handle_quoted_args(char *str)
{
	clean_quotes(str, 39, ' ', CTRL_SPC);
	clean_quotes(str, 34, ' ', CTRL_SPC);
	clean_quotes(str, 34, '>', CTRL_H);
	clean_quotes(str, 39, '<', CTRL_L);
	clean_quotes(str, 34, '<', CTRL_L);
	clean_quotes(str, 39, '>', CTRL_H);
}

void	restore_io_quoted(char **array)
{
	int	index;

	index = 0;
	while(array[index])
	{
		ft_memrpl(array[index], CTRL_H, '>', ft_strlen(array[index]));
		ft_memrpl(array[index], CTRL_L, '<', ft_strlen(array[index]));
		index++;
	}
}