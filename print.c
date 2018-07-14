/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		print_turn(t_lemin *lem, int ant, int way, int count)
{
	t_slist		*temp;
	int			stop;

	while (++ant < lem->ants + 1)
	{
		stop = 0;
		way = -1;
		while (lem->ways[++way] && !stop && (temp = lem->ways[way]))
		{
			while (temp && !stop)
			{
				if (temp->ant == ant && temp->num != 0)
				{
					if (++count > 1)
						ft_printf(" ");
					lem->col == 0 ? ft_printf("L%d-%s", ant, temp->room) :
						ft_printf(CB_GREEN "L%d-%s" C_RESET, ant, temp->room);
					stop = 1;
				}
				temp = temp->next;
			}
		}
	}
	if (count)
		ft_printf("\n");
}

void		print_result(t_lemin *lem, int turns[])
{
	int			ant;
	int			on;
	int			way;

	ant = 1;
	on = 1;
	while (on)
	{
		way = 0;
		while (lem->ways[way])
		{
			if (turns[way])
			{
				lem->ways[way]->ant = ant;
				ant += 1;
				turns[way] -= 1;
			}
			way++;
		}
		if (move_ants(lem, -1, 0, 0) > 0)
			on = 1;
		else
			on = 0;
		print_turn(lem, 0, 0, 0);
	}
}

void		print_str(t_lemin *lem, int i)
{
	char	**arr;

	arr = lem->arr;
	while (arr[i])
	{
		if (!ft_strcmp(arr[i], "##start") || !ft_strcmp(arr[i], "##end") ||
			!(arr[i][0] == '#' && arr[i][1] == '#' && arr[i][2] != '#'))
			lem->col == 0 ? ft_printf("%s\n", arr[i]) :
				ft_printf(C_YELLOW "%s\n" C_RESET, arr[i]);
		i++;
	}
	i = 0;
	ft_printf("\n");
}
