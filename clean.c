/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itiievsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 09:50:55 by itiievsk          #+#    #+#             */
/*   Updated: 2018/06/07 09:50:59 by itiievsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		clean_all(t_lemin *lem, int way, int x)
{
	t_slist		*temp;

	free(lem->string);
	free(lem->line);
	free(lem->start);
	free(lem->end);
	while (lem->arr[x])
		free(lem->arr[x++]);
	free(lem->arr);
	while (lem->list)
	{
		temp = lem->list;
		lem->list = lem->list->next;
		free(temp->room);
		free(temp);
	}
	while (lem->ways[++way])
	{
		while (lem->ways[way])
		{
			temp = lem->ways[way];
			lem->ways[way] = (lem->ways[way])->next;
			free(temp->room);
			free(temp);
		}
	}
}

void		error_exit(t_lemin *lem, int x)
{
	t_slist		*temp;

	free(lem->string);
	free(lem->line);
	free(lem->start);
	free(lem->end);
	while (lem->arr[x])
		free(lem->arr[x++]);
	free(lem->arr);
	while (lem->list)
	{
		temp = lem->list;
		lem->list = lem->list->next;
		free(temp->room);
		free(temp);
	}
	ft_printf("ERROR\n");
	exit(-1);
}
