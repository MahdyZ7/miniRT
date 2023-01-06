/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_vector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 09:26:06 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/05 16:45:29 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int		vector_init(t_vec *vec, t_list *tmp)
{
	float	x;
	float	y;
	float	z;

	if (fill_coord((char *)tmp->content, &x, &y, &z))
		return (1);
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (0);
}

int	fill_coord(char *coord, float *x, float *y, float *z)
{
	if (fill_first_element(coord, x)
		|| fill_second_element(coord, y)
		|| fill_thrid_element(coord, z))
		return (1);
	else
		return (0);
}

int	fill_first_element(char *coord, float *x)
{
	char	*fill_me;
	float	num;
	int		step_by;

	fill_me = NULL;
	step_by = ft_strnchr(coord, ',');
	if (step_by == -1)
		return (1);
	fill_me = ft_substr(coord, 0, step_by);
	if (!fill_me)
		return (0);
	num = ft_atof(fill_me);
	free(fill_me);
	*x = num;
	return (0);
}

int	fill_second_element(char *coord, float *y)
{
	char	*fill_me;
	int		step_by;
	float	num;

	fill_me = NULL;
	coord = &coord[ft_strnchr(coord, ',') + 1];
	step_by = ft_strnchr(coord, ',');
	if (step_by == -1)
		return (1);
	fill_me = ft_substr(coord, 0, step_by);
	if (!fill_me)
		return (0);
	num = ft_atof(fill_me);
	free(fill_me);
	*y = num;
	return (0);
}

int	fill_thrid_element(char *coord, float *z)
{
	float	num;

	coord = &coord[ft_strnchr(coord, ',') + 1];
	coord = &coord[ft_strnchr(coord, ',') + 1];
	if (!coord)
		return (1);
	num = ft_atof(coord);
	*z = num;
	return (0);
}
