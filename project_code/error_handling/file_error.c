/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 15:28:03 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/24 08:11:54 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	not_valid_file(int argc, char **argv)
{
	if (argc != 2)
		return (parse_error_message());
	if (!argv[1])
		return (parse_error_message());
	if (bad_file(argv))
		return (parse_error_message());
	return (0);
}

int	bad_file(char **argv)
{
	int	len;
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	len = ft_strlen(argv[1]);
	if (!(argv[1][len - 1] == 't'
		&& argv[1][len - 2] == 'r'
		&& argv[1][len - 3] == '.')
		)
		return (1);
	return (0);
}

int	initial_error_scan(t_list **all_map_items)
{
	t_list	*tmp;

	tmp = *all_map_items;
	if (!tmp)
		return (1);
	if (not_valid_element(tmp))
	{
		return (1);
	}
	while (tmp)
	{
		if (!ft_the_strcmp((char *)tmp->content, "\n"))
		{
			if (!tmp->next)
				return (0);
			if (not_valid_element(tmp->next))
			{
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	parse_error_message(void)
{
	write(2, "Error!\nFile Parsing Error,\n", 27);
	return (1);
}

int	file_reading_error_message(void)
{
	write(2, "Error!\nFile formmating error,\n", 27);
	return (1);
}
