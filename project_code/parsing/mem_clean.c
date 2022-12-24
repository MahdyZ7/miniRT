/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:05:27 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 09:07:50 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	clean_scene(t_scene scene)
{
	if (scene.spheres)
	{
		free(scene.spheres);
		scene.spheres = NULL;
	}
	if (scene.plane)
	{
		free(scene.plane);
		scene.plane = NULL;
	}
	if (scene.cylinder)
	{
		free(scene.cylinder);
		scene.cylinder = NULL;
	}
}
