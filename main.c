/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:54 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:56 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	parse_map(t_lemin *lem, int ret, int index)
{
	while ((ret = get_next_line(0, &lem->line)) > 0 && ++index)
	{
		if (index == 1)
			lem->ants = ft_atoi(lem->line);
		ft_printf("%s\n", lem->line);
	}
}

static void	init_struct(t_lemin *lem)
{
	lem->ants = 0;
}

int			main(void)
{
	t_lemin		*lem;

	lem = (t_lemin*)malloc(sizeof(t_lemin));
	init_struct(lem);
	parse_map(lem, 0, 0);
	ft_printf("\n");
	free(lem);
	return (0);
}
