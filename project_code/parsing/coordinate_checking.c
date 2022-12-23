/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate_checking.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 18:26:35 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/23 18:50:39 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_coordinate_range(t_list *tmp)
{
	char	*coord;

	printf("\nstarted the coordinate range check\n");
	coord = NULL;
	if (check_coordinates_error(tmp))
		return (1);
	coord = (char *)tmp->content;
	if (inspect_first_element(coord)
		|| inspect_second_element(coord)
		|| inspecet_thrid_element(coord))
		return (1);
	else
		return (0);
}

int	inspect_first_element(char *coord)
{
	char	*check_me;
	float	num;
	int		step_by;

	check_me = NULL;
	step_by = ft_strnchr(coord, ',');
	if (step_by == -1)
		return (1);
	check_me = ft_substr(coord, 0, step_by);
	if (!check_me)
		return (0);
	num = ft_atof(check_me);
	printf("inspecting first element %s = %f\n", check_me, num);
	free(check_me);
	if (num > 255 || num < 0)
	{
		printf("%f Out of range\n", num);
		return (1);
	}
	return (0);
}

int	inspect_second_element(char *coord)
{
	char	*check_me;
	int		step_by;
	float	num;

	check_me = NULL;
	coord = &coord[ft_strnchr(coord, ',') + 1];
	step_by = ft_strnchr(coord, ',');
	printf("\n shoudl step by %d\n", step_by);
	if (step_by == -1)
		return (1);
	check_me = ft_substr(coord, 0, step_by);
	if (!check_me)
		return (0);
	num = ft_atof(check_me);
	printf("inspecting second element %s = %f\n", check_me, num);
	free(check_me);
	if (num > 255 || num < 0)
	{
		printf("%f Out of range\n", num);
		return (1);
	}
	return (0);
}

int	inspecet_thrid_element(char *coord)
{
	float	num;

	coord = &coord[ft_strnchr(coord, ',') + 1];
	printf("now coord = %s\n", coord);
	coord = &coord[ft_strnchr(coord, ',') + 1];
	if (!coord)
		return (1);
	num = ft_atof(coord);
	printf("inspecting third element %s = %f\n", coord, num);
	if (num > 255 || num < 0)
	{
		printf("%f Out of range\n", num);
		return (1);
	}
	return (0);
}
