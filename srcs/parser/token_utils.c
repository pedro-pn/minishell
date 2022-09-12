/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 20:28:23 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/11 20:38:22 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_quotes(char **array)
{
	int	index;

	index = 0;
	while(array[index])
	{
		ft_memrpl(array[index], 1, 32, ft_strlen(array[index]));
		ft_memrpl(array[index], 2, 34, ft_strlen(array[index]));
		ft_memrpl(array[index], 3, 39, ft_strlen(array[index]));
		index++;
	}
}