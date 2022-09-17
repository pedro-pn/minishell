/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 15:38:04 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/17 15:50:10 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_cmds_quotes(char **cmds)
{
	int	i;

	i = -1;
	if (!cmds)
		return;
	while (i++, cmds[i])
	{
		if (ft_strchr(cmds[i], '\'') || ft_strchr(cmds[i], '\"'))
			remove_quotes(&cmds[i]);
	}
}

void	clean_infile_quotes(char **infile)
{
	if (!*infile)
		return;
	if (ft_strchr(*infile, '\'') || ft_strchr(*infile, '\"'))
		remove_quotes(infile);
}

void	clean_outfile_quotes(char **outfile)
{
	if (!*outfile)
		return;
	if (ft_strchr(*outfile, '\'') || ft_strchr(*outfile, '\"'))
		remove_quotes(outfile);
}

void	clean_delimiter_quotes(char **delimiter)
{
	if (!*delimiter)
		return;
	if (ft_strchr(*delimiter, '\'') || ft_strchr(*delimiter, '\"'))
		remove_quotes(delimiter);
}