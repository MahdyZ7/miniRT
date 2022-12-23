/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:55:05 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/21 20:13:57 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Compare the first "n" chars from strings "s1" & "s2".
Return the diffrence in the first char or 0 if no diffrence is found
**NOT PROTECTED VS NULL INPUT**/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	pos;

	pos = 0;
	if (!n)
		return (0);
	while (pos < (n - 1) && s1[pos] && s2[pos] && (unsigned char)s1[pos]
		== (unsigned char)s2[pos])
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}

int	ft_the_strcmp(const char *s1, const char *s2)
{
	size_t	pos;
	size_t	len_first;
	size_t	len_second;
	size_t	n;

	n = 0;
	pos = 0;
	if (!s1 || !s2)
		return (1);
	len_first = ft_strlen(s1);
	len_second = ft_strlen(s2);
	if (len_first > len_second)
		n = len_first;
	else
		n = len_second;
	while (pos < (n - 1) && s1[pos] && s2[pos] && (unsigned char)s1[pos]
		== (unsigned char)s2[pos])
		pos++;
	return ((unsigned char)s1[pos] - (unsigned char)s2[pos]);
}
