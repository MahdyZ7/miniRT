/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:39:52 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/21 20:09:42 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		ten_pow(int n);
static void		init_atof_kit(t_atof_kit *a);
static float	calculate_result(struct s_atof_kit *a);

float	ft_atof(const char *str)
{
	struct s_atof_kit	a;

	init_atof_kit(&a);
	if (!str)
		return (0);
	if (str[0] == '-')
	{
		str++;
		a.sign = -1;
	}
	a.dot_location = ft_strnchr(str, '.');
	if (a.dot_location == -1)
	{
		a.result = (float)ft_atoi(str);
		return (a.result);
	}
	a.first_part = ft_substr(str, 0, a.dot_location);
	a.second_part = ft_substr(str, a.dot_location + 1, ft_strlen(str));
	a.ten_pow_len_second = ten_pow(ft_strlen(a.second_part));
	a.result = calculate_result(&a);
	free(a.first_part);
	free(a.second_part);
	return (a.result * (float)a.sign);
}

static float	calculate_result(struct s_atof_kit *a)
{
	a->result = (float)ft_atoi(a->first_part)
		+ ((float)((long)ft_atoi(a->second_part) % a->ten_pow_len_second)
			/ (float)a->ten_pow_len_second);
	return (a->result);
}

static long	ten_pow(int n)
{
	int		i;
	long	result;

	i = 0;
	result = 1;
	while (i < (n))
	{
		result *= 10;
		i++;
	}
	return (result);
}

static void	init_atof_kit(t_atof_kit *a)
{
	a->first_part = NULL;
	a->second_part = NULL;
	a->sign = 1;
	a->result = 1.0;
	a->dot_location = 1;
	a->ten_pow_len_second = 0;
}
