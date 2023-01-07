/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizers_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 02:07:12 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/07 18:37:00 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	vis_vector(t_vec vec)
{
	printf("(%3.2f, %3.2f, %3.2f)", vec.x, vec.y, vec.z);
}

void	vis_planes(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->plane[i].n_planes)
	{
		vis_single_plane(scene->plane[i]);
		i++;
	}
}

void	vis_single_sphere(t_sphere sphere)
{
	printf("sp %3.2f,%3.2f,%3.2f	%3.2f	%3.2f,%3.2f,%3.2f\n",
		sphere.center.x, sphere.center.y,
		sphere.center.z, sphere.diameter,
		sphere.color.x, sphere.color.y,
		sphere.color.z);
}

void	vis_single_plane(t_plane plane)
{
	printf("pl %3.2f,%3.2f,%3.2f	%3.2f,%3.2f,%3.2f	%3.2f,%3.2f,%3.2f\n",
		plane.pos.x, plane.pos.y, plane.pos.z,
		plane.orientation.x, plane.orientation.y, plane.orientation.z,
		plane.color.x, plane.color.y, plane.color.z);
}

void	vis_elements(t_scene *scene)
{
	printf("A %3.2f	%3.2f,%3.2f,%3.2f\n", scene->amb_light.ratio,
		scene->amb_light.color.x, scene->amb_light.color.y,
		scene->amb_light.color.z);
	printf("L %3.2f,%3.2f,%3.2f	%3.2f	%3.2f,%3.2f,%3.2f\n",
		scene->light.pos.x,
		scene->light.pos.y, scene->light.pos.z, scene->light.brightness,
		scene->light.color.x, scene->light.color.y, scene->light.color.z);
	printf("C %3.2f,%3.2f,%3.2f	%3.2f,%3.2f,%3.2f	%3.2f\n",
		scene->camera.view_point.x,
		scene->camera.view_point.y, scene->camera.view_point.z,
		scene->camera.orientation.x, scene->camera.orientation.y,
		scene->camera.orientation.z, scene->camera.view_field);
}
