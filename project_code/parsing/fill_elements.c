/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 08:17:10 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 19:37:08 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	fill_ambient_light(
	t_list **all_map_items, t_scene *scene)
{
	t_list	*tmp;

	tmp = *all_map_items;
	tmp = get_next_occurance(tmp, "A");
	tmp = tmp->next;
	scene->amb_light.ratio = ft_atof((char *)tmp->content);
	if (vector_init(&scene->amb_light.color, tmp->next))
		return (1);
	scene->amb_light.color = vec_scalar_mult(&scene->amb_light.color,
			1 / 255.0);
	return (0);
}

int	fill_light(
	t_list **all_map_items, t_scene *scene)
{
	t_list	*tmp;

	tmp = *all_map_items;
	tmp = get_next_occurance(tmp, "L");
	tmp = tmp->next;
	if (vector_init(&scene->light.pos, tmp))
		return (1);
	scene->light.brightness = ft_atof((char *)tmp->next->content);
	if (vector_init(&scene->light.color, tmp->next->next))
		return (1);
	scene->light.color = vec_scalar_mult(&scene->light.color, 1 / 255.0);
	return (0);
}

int	fill_camera(
	t_list **all_map_items, t_scene *scene)
{
	t_list	*tmp;

	tmp = *all_map_items;
	tmp = get_next_occurance(tmp, "C");
	tmp = tmp->next;
	if (vector_init(&scene->camera.view_point, tmp))
		return (1);
	if (vector_init(&scene->camera.orientation, tmp->next))
		return (1);
	if (check_normalized_coord(scene->camera.orientation))
		return (1);
	scene->camera.view_field = ft_atof((char *)tmp->next->next->content);
	return (0);
}

void	vec_init(t_vec *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}
