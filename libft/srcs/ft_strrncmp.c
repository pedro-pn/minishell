/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppaulo-d <ppaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:11:02 by ppaulo-d          #+#    #+#             */
/*   Updated: 2022/09/26 17:43:21 by ppaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*string_inverter(const char *str);

/** This functions compares the last n bytes of the two strings pointed to by s1
 *  and s2.
 * @param s1 First string to compare.
 * @param s2 Second string to compare.
 * @param n The number of bytes to compare.
 * @return 0 if both strings are equal, a positive integer if s1 is larger than
 * s2, and a negative integer if s1 is shorter than s2.
 * */
int	ft_strrncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;
	char	*inv_s1;
	char	*inv_s2;
	int		value;

	inv_s1 = string_inverter(s1);
	inv_s2 = string_inverter(s2);
	value = 0;
	index = 0;
	while ((index < n) && (inv_s1[index] || inv_s2[index]))
	{
		value = (unsigned char) inv_s1[index] - (unsigned char) inv_s2[index];
		if (value != 0)
		{
			free(inv_s1);
			free(inv_s2);
			return (value);
		}
		index++;
	}
	free(inv_s1);
	free(inv_s2);
	return (value);
}

static char	*string_inverter(const char *str)
{
	int		str_len;
	int		index;
	char	*inv_str;

	str_len = ft_strlen(str);
	inv_str = ft_calloc(str_len + 1, sizeof(*inv_str));
	index = 0;
	str_len--;
	while (str_len >= 0)
	{
		inv_str[index] = str[str_len];
		str_len--;
		index++;
	}
	return (inv_str);
}
