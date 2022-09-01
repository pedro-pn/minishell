/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frosa-ma <frosa-ma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 13:25:12 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/01 06:12:44 by frosa-ma         ###   ########.fr       */
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

/* Cleans the struct s_cmd*/
void	clean_s_cmd(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	clean_array((void **)cmd->cmd);
	free(cmd->in_file);
	free(cmd->out_file);
	free(cmd->path);
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->path = NULL;
	free(cmd);
	cmd = NULL;
}

/* Cleans struct s_prompt - except the directory*/
void	clean_prompt(t_prompt *prompt)
{
	free(prompt->line);
	free(prompt->tb_line);
	free(prompt->message);
	prompt->line = NULL;
	prompt->tb_line = NULL;
	prompt->message = NULL;
}
