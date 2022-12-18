/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:22:05 by ahsalem           #+#    #+#             */
/*   Updated: 2022/12/18 11:59:38 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
//remember to take the nulls
//handle 'unclosed quote
//remember to handle this case "he hello"ho 
//remember to handle this case also 'how is is one sh'unk

// void	spaces_smash(t_smash_kit *s, char *line, t_list **head, int *exit_status)
// {
// 	char	*smashed_arg;

// 	smashed_arg = NULL;
// 	if (!line[s->i])
// 		return ;
// 	if (line[s->i] == '"')
// 		s->flag = '"';
// 	else if (line[s->i] == '\'')
// 		s->flag = '\'';
// 	if (line[s->i] == ' ' && line[s->i + 1] && line[s->i + 1] != ' ')
// 		s->start = s->i + 1;
// 	else if (line[s->i] == ' ')
// 		;
// 	else if ((s->flag == 's' && (line[s->i + 1] == ' '
// 				|| (check_new_line(line, s->i + 1))))
// 		|| ((s->i + 1) >= s->line_len))
// 	{
// 		filling_normal_spaced_word(
// 			s, smashed_arg, head, exit_status);
// 	}
// }

// void	filling_normal_spaced_word(
// 		t_smash_kit *s, char *smashed_arg, t_list **head, int *exit_status)
// {
// 	s->end = s->i;
// 	smashed_arg = ft_substr(s->line, s->start, s->end - s->start + 1);
// 	smashed_arg = expand_var(s, smashed_arg, exit_status);
// 	if (!(!smashed_arg[0] && s->line[0]))
// 	{
// 		s->tmp = fill_cmd_node(smashed_arg, 'c');
// 		ft_lstadd_back(head, s->tmp);
// 	}
// 	else
// 		free(smashed_arg);
// 	s->flag = 'i';
// }
