/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:25:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/08/24 14:09:02 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Cleans a two dimensional array */
void	clean_array(void **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		array[index] = NULL;
		index++;
	}
	free(array);
	array = NULL;
}

/* Essa função é só para poder passar clean_array para ft_lstclear. Provavelmente
ela n será necessária, deixei apenas como teste. Pretendo liberar esse array
durante a execução*/
void	clean_cmd_lines(void *content)
{
	clean_array(((void **) content));
}