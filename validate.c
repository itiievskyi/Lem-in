/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void check_lines(t_lemin *lem, int i)
{
	while (lem->arr[i])
	{
		if ((lem->arr[i])[0] == ' ')
		{
			cut_array(lem, i);
			break ;
		}
		i++;
	}
//	i = 0;
//	while (lem->arr[i])
//		i++;
	if (i < 6)
		error_exit(lem, 0);
}

void		validate(t_lemin *lem)
{
	int i;

	i = 0;
	if (!lem)
		error_exit(lem, 0);
	while ((lem->arr[0])[i] != '\0')
		if (!ft_isdigit(lem->arr[0][i++]) || ft_atoi(lem->arr[0]) == 0)
			error_exit(lem, 0);
	check_lines(lem, 0);
}
