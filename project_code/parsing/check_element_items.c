/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element_items.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 23:54:06 by ahsalem           #+#    #+#             */
/*   Updated: 2023/01/06 20:25:32 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	check_coordinates_error(t_list *tmp)
{
	if (!tmp)
		return (1);
	if (!is_cordinate((char *)tmp->content))
	{
		// ft_printf("not coordinate :(\n");
		return (1);
	}
	else
		return (0);
	return (1);
}

int	is_cordinate(char *coordinate)
{
	int	i;
	int	items;

	items = 0;
	i = 0;
	if (!coordinate)
		return (0);
	while (coordinate[i] && items < 3)
	{
		if (ft_is_float_and_update_i(coordinate, &i))
		{
			if ((items < 2 && coordinate[i] != ',')
				|| (items == 2 && coordinate[i] != '\0'))
				return (0);
		}
		else
			return (0);
		items++;
		if (i > ft_strlen(coordinate) - 1)
			break;
		i++;
	}
	return (1);
}

int	ft_is_float_and_update_i(char *check_me, int *i)
{
	// ft_printf("checking %s\n",& check_me[*i]);
	if (check_me[*i] == '+' || check_me[*i] == '-')
		*i = *i + 1;
	if (!ft_isdigit(check_me[*i]))
		return (0);
	while (ft_isdigit(check_me[*i]))
	{
		*i = *i + 1;
	}
	if (check_me[*i] == '.')
	{
		*i = *i + 1;
		while (ft_isdigit(check_me[*i]))
			*i = *i +1;
	}
	return (1);
}

t_list	*get_next_occurance(t_list *tmp, char *element)
{
	while (tmp)
	{
		if (!ft_the_strcmp((char *)tmp->content, element))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

//isaad;
//ircserv;