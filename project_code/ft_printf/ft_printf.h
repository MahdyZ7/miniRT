/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahsalem <ahsalem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 11:19:14 by ayassin           #+#    #+#             */
/*   Updated: 2022/12/24 09:34:13 by ahsalem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_printf_H
# define FT_printf_H
# include <stdarg.h>
# include <unistd.h>
# include "../libft/libft.h"

int		ft_printf(const char *str, ...);
int		ft_printfstr(char *str);
int		ft_printfptr(unsigned long long int p);
int		ft_printfunsgned(unsigned int p, int base, int upper);
int		ft_printfint(int num);
#endif